#include <csmi.h>
#include <csmi_aux.h>
#include <cdn_stdtypes.h>
#include <cdn_errno.h>
#include <stdlib.h>
#include <string.h>
#include <log.h>

#define dbg_err printf
#define dbg_warn printf
#define dbg_inf printf
#define dbg_tmp printf

#define malloc_ malloc
#define realloc_ realloc
#define free_ free

#define sort sort_by_adj_pr_freq_desc // qsort

#define SF_MAPPING_EMPTY_SLOT ((uint16_t)-1)
#define SF_MAPPING_CONTROL_SLOT ((uint16_t)-2)
#define SF_MAPPING_COLLISION ((uint16_t)-3)
#define SF_MAPPING_CHANNEL(CH_) (uint16_t)((CH_) & 0xFF)

#define GET_PRESENCE_RATE(FAM_, FREQ_) \
	((((FAM_) & 0xF) << 3) | ((FREQ_) & 0x7))
#define GET_PRESENCE_RATE_FAM(PR_) \
	(((PR_) >> 3) & 0xF)
#define GET_PRESENCE_RATE_FREQ(PR_) \
	((PR_) & 0x7)
#define MAX_PR_FREQ get_presence_rate_hz(GET_PRESENCE_RATE(0, 7))
#define MIN_PR_FREQ get_presence_rate_hz(GET_PRESENCE_RATE(2, 0))

typedef enum {
	/** PR is a multiplicity of 12k (PR[2..0] = 0b0000) */
	CH_PR_FAM_MUL_12K,
	/** PR is a multiplicity of 11.025k (PR[2..0] = 0b0001) */
	CH_PR_FAM_MUL_11025,
	/** PR is power of two(PR[2..0] = 0b0010) */
	CH_PR_FAM_POW_2,
	/** None of above, value illegal (PR[2..0] is undefined) */
	CH_PR_FAM_NONE
} channel_pr_family;

/**
 * Channel allocation descriptor.
 * @field ch pointer to associated Channel descriptor.
 * @field family Presence Rate family.
 * @field adj_family Adjusted PR family.
 * @field adj_pr_freq Adjusted Presence Rate frequency (expressed in Hertz).
 * @field si Segment Interval value.
 * @field so Segment Offset value.
 * @field sw Segment Width value (expressed in slots).
 * @field sd Segment Distribution value.
 * @field is_iso True for isochronous mode, false for pushed/pulled.
 */
typedef struct {
	channel_desc *ch;

	channel_pr_family family;
	channel_pr_family adj_family;

	uint32_t adj_pr_freq;

	uint16_t si;
	uint16_t so;
	uint16_t sd; // copy to ch->sd
	uint8_t sw; // copy to ch->sl

	bool is_iso;

	// For debugging purposes only.
	bool has_longest_sl;
	bool has_max_freq;
} alloc_desc;

typedef int (*fptr)(void const *a, void const *b);

static void sort_by_adj_pr_freq_desc(alloc_desc **desc, size_t count,
		size_t size, int (*not_used)(void const *, void const *))
{
	size_t i, j;
	alloc_desc *swap;

	if (count < 2 || desc == NULL)
		return;

	for (i = 0; i < count - 1; ++i) {
		for(j = i + 1; j < count; ++j) {
			if (desc[j]->adj_pr_freq > desc[i]->adj_pr_freq) {
				swap = desc[i];
				desc[i] = desc[j];
				desc[j] = swap;
			}
		}
	}
}

/**
 * Compares descriptors by adjusted PR frequency (ascending)
 * @param[in] desca First descriptor to compare with.
 * @param[in] descb Second descriptor to compare with.
 * @returns 0 if descriptors have same feature, negative if A is first,
 *	positive if B is first.
 */
static int compare_by_adj_pr_freq_desc(void const *desca, void const *descb)
{
	alloc_desc const *a = *(alloc_desc const **)desca;
	alloc_desc const *b = *(alloc_desc const **)descb;

	dbg_tmp("Comparing %u with %u\n", a->adj_pr_freq, b->adj_pr_freq);
	dbg_tmp("Comparing %p with %p\n", a, b);

	if (a->adj_pr_freq < b->adj_pr_freq)
		return 1;

	if (a->adj_pr_freq > b->adj_pr_freq)
		return -1;

	return 0;
}

/**
 * Compares Channels configuration.
 * @returns 0 if values are the same.
 * @returns non-0 if values differ.
 */
static inline int compare_channels(channel_desc const *cha,
		channel_desc const *chb) {
	return (cha->cn != chb->cn)
		|| (cha->sd != chb->sd)
		|| (cha->tp != chb->tp)
		|| (cha->sl != chb->sl);
}

/**
 * Compares Channels Content configuration.
 * @returns 0 if values are the same.
 * @returns non-0 if values differ.
 */
static inline int compare_channels_content(channel_desc const *cha,
		channel_desc const *chb) {
	return (cha->fl != chb->fl)
		|| (cha->pr != chb->pr)
		|| (cha->af != chb->af)
		|| (cha->cl != chb->cl)
		|| (cha->dt != chb->dt)
		|| (cha->dl != chb->dl);
}

/**
 * Returns frequency in Hertz for given Presence Rate or 0 if Presence Rate
 * value is invalid.
 */
static inline uint32_t get_presence_rate_hz(uint8_t pr)
{
	// Presence Rate values in Hz from table 62 of the SLIMbus spec. v1.1
	// Rows represents three Presence Rate families - 12k, 11025 and pow2.
	// Columns represents available frequencies of each family.
	static uint32_t const pr_table[3][8] = {
		{ 0, 12000, 24000, 48000, 96000, 192000, 384000, 768000 },
		{ 0, 11025, 22050, 44100, 88200, 176400, 352800, 705600 },
		{ 4000, 8000, 16000, 32000, 64000, 128000, 256000, 512000 }
	};

	uint32_t fam = GET_PRESENCE_RATE_FAM(pr);
	uint32_t freq = GET_PRESENCE_RATE_FREQ(pr);

	if (fam < CH_PR_FAM_NONE)
		return pr_table[fam][freq];

	return 0;
}

/**
 * Subframe Mode descriptor.
 * @field ctrl_slots Control space width (expressed in Slots, 0 if not
 *		applicable).
 * @field total_slots Subframe length (expressed in Slots, 0 if not applicable)
 */
typedef struct {
	uint8_t ctrl_slots;
	uint8_t total_slots;
} subframe_mode_descr;

#define NUM_OF_SUBFRAME_MODES 32
#define INVALID_SUBFRAME_MODE NUM_OF_SUBFRAME_MODES
/**
 * Array with available Subframe Modes (according to table 15 of
 * SLIMbus(TM) specification, indexed by binary SM value)
 * Zero means reserved and should not be used.
 */
static subframe_mode_descr const subframe_modes[NUM_OF_SUBFRAME_MODES] = {
	{8, 8},
	{0, 0},
	{0, 0},
	{0, 0},
	{1, 6},
	{1, 8},
	{1, 24},
	{1, 32},
	{2, 6},
	{2, 8},
	{2, 24},
	{2, 32},
	{3, 6},
	{3, 8},
	{3, 24},
	{3, 32},
	{4, 6},
	{4, 8},
	{4, 24},
	{4, 32},
	{0, 0},
	{6, 8},
	{6, 24},
	{6, 32},
	{8, 24},
	{8, 32},
	{12, 24},
	{12, 32},
	{16, 24},
	{16, 32},
	{24, 0},
	{24, 32}
};


/**
 * Tries to find Subframe Mode value from given parameters
 * (according to table 15 of SLIMbus spec.)
 * @param[out] subframe_mode Address where Subframe Mode value
 *	will be written, if found.
 * @param total_slots Total number of slots in subframe (Subframe Width).
 * @param ctrl_slots Number of control slots in subframe (Control Width).
 * @returns true if valid Subframe Mode value was found or false, if not.
 */
static inline bool subframe_modes_get_subframe_mode_val(
		uint8_t *subframe_mode, uint8_t total_slots, uint8_t ctrl_slots)
{
	uint16_t i;

	for (i = 0; i < NUM_OF_SUBFRAME_MODES; ++i) {
		if (subframe_modes[i].total_slots == total_slots
				&& subframe_modes[i].ctrl_slots == ctrl_slots) {
			break;
		}
	}

	// Check if value is out of range or reserved
	if ((i >= NUM_OF_SUBFRAME_MODES) // out of range
		|| (i == 0x1E) // reserved (same as 0)
		|| (i == 0x14) // reserved (same as 0)
		|| (i == 0x03) // reserved (same as 7)
		|| (i == 0x02) // reserved (same as 0)
		|| (i == 0x01)) { // reserved (same as 5)
		*subframe_mode = INVALID_SUBFRAME_MODE;
		return false;
	}

	*subframe_mode = i;

	return true;
}

/**
 * Root Frequency descriptor.
 * @field frequency Root Frequency value (expressed in Hertz).
 * @field phase_modulus Phase Modulus value.
 */
typedef struct {
	uint32_t frequency;
	uint16_t phase_modulus;
} root_freq_descr;

/**
 * Array with available Root Frequencies (according to table 17 of SLIMbus(TM)
 * specification, indexed by binary RF value).
 */
static root_freq_descr const root_frequencies[16] = {
	{		0,	 160},
	{24576000,	 160},
	{22579200,	 147},
	{15360000,	 100},
	{16800000,	 875},
	{19200000,	 125},
	{24000000,	 625},
	{25000000, 15625},
	{26000000,	8125},
	{27000000,	5625},
	// The rest is set to 0
};

/**
 * Tries to find Root Frequency value from given parameters
 * (according to table 17 of SLIMbus spec.)
 * @param[in] root_frequency Root Frequency (expressed in Hertz).
 * @returns Root Frequency value (0 if not found).
 */
static inline uint8_t get_root_freq_val(uint32_t root_frequency)
{
	uint16_t i;
	uint16_t const rf_count = sizeof(root_frequencies)
		/ sizeof(root_frequencies[0]);

	for (i = 0; i < rf_count; ++i) {
		if (root_frequencies[i].frequency == root_frequency)
			return i;
	}

	return 0; // Not indicated - assume invalid
}

/**
 * Root Frequency for given value.
 * (according to values from table 17 of the SLIMbus spec.)
 * @param[in] root_frequency Root Frequency value from CSMI_RootFrequency enum.
 * @returns Root Frequency frequency in Hz (0 if not found).
 */
static inline uint32_t get_root_freq_hz(uint8_t root_frequency)
{
	if (root_frequency > 9) // invalid input
		return 0;

	return root_frequencies[root_frequency].frequency;
}
/**
 * Computes Segment Interval for given channel freq.
 * @param bus_freq Bus frequency (Root Freq. after applying Clock Gear).
 * @param chan_freq_rate Channel frequency rate (expressed in Hertz).
 * @param[out] si_family Place where Segment Interval family is stored.
 * @param[out] adjusted_si Place where adjusted (to its family)
 *	Segment Interval is stored.
 * @returns True if channel can be considered as ISO, false otherwise.
 */
static bool compute_seg_int(uint32_t bus_freq, uint32_t chan_freq_rate,
		channel_pr_family *si_family, uint32_t *adjusted_si)
{
	uint16_t const seg_int = (bus_freq / chan_freq_rate) >> 2;
	bool const is_iso = (bus_freq % chan_freq_rate) == 0;

	uint16_t i;
	uint16_t best_fit_i = 0;
	uint32_t best_fit_dist = 10000; // invalid value

	// i = 0..9    -> SI = 3..1536
	// i = 10..18  -> SI = 2..512

	for (i = 0; i < 19; ++i) {
		bool const mul_3 = i < 10;
		uint32_t const two_power = 1 << (mul_3 ? i : i - 10);
		uint32_t const val = mul_3 ? 3 * two_power : two_power;

		if (is_iso && (val == seg_int)) {
			best_fit_i = i;
			*adjusted_si = val;
			best_fit_dist = 0;
			break;
		} else if (!is_iso && val > seg_int && val - seg_int < best_fit_dist) {
			best_fit_i = i;
			*adjusted_si = val;
			best_fit_dist = val - seg_int;
		}
	}

	*si_family = best_fit_i < 10 ? CH_PR_FAM_MUL_12K : CH_PR_FAM_POW_2;

	return is_iso;
}

/**
 * Computes Presence Rate (only part - PR[2..0]) from given freq. rate.
 * @param[in] freq_rate_hz Frequency rate to be converted (expressed in Hertz).
 * @param[in] pr_family Presence Rate family.
 * @param[in] must_be_larger True if computed PR MUST be larger,
 *	even in case that given freq. rate can be expressed
 * with exact PR. If PR family does not contain "exact" freq. rate
 * representation - the closest LARGER is selected.
 * @param[out] pr_freq_rate Presence Rate frequency (expressed in Hertz).
 * @returns Presence Rate, bits [2..0]. Value CH_PR_FAM_NONE should be
 *	treated as an error.
*/
static uint8_t compute_pr_from_freq(uint32_t freq_rate_hz,
		channel_pr_family pr_family, bool must_be_larger,
		uint32_t *pr_freq_rate)
{
	uint8_t result_pr;
	uint32_t current_freq_rate;

	///dbg_tmp("freq_rate_hz: %u, pr_fam: %u, must_be_larger: %u\n",
	/// 	   freq_rate_hz, pr_family, must_be_larger);

	switch (pr_family) {
		case CH_PR_FAM_MUL_12K:
			result_pr = 1;
			current_freq_rate = 12000;
			break;

		case CH_PR_FAM_MUL_11025:
			result_pr = 1;
			current_freq_rate = 11025;
			break;

		case CH_PR_FAM_POW_2:
			result_pr = 0;
			current_freq_rate = 4000;
			break;

		default:
			dbg_warn("Unknown Presence Rate family.\n");
			*pr_freq_rate = 0; // 0 is invalid value for PR.

			return CH_PR_FAM_NONE;
	}

	///dbg_tmp("current_freq_rate: %u\n", current_freq_rate);

	if (must_be_larger)
		++freq_rate_hz;

	while (current_freq_rate < freq_rate_hz) {
		++result_pr;
		current_freq_rate <<= 1;
		///dbg_tmp("current_freq_rate: %u\n", current_freq_rate);
	}

	*pr_freq_rate = current_freq_rate;

	return result_pr;
}

/**
 * Computes Segment Distribution binary value.
 * Function assumes that SI has VALID VALUE (as listed in table 20 of the
 *		SLIMbus spec.).
 * @param si Segment Interval value.
 * @param so Segment Offset value.
 * @returns Segment Distribution value.
 */
static uint16_t compute_segment_dist(uint16_t si, uint16_t so)
{
	bool const si_2 = (si & (si - 1)) == 0; // only one bit is set?
	uint16_t i;
	uint16_t result;

	for (i = 0; i < 10; ++i) {
		if ((si >> i) & 1)
			break;
	}

	result = (so & ~(0xFFFF << i));

	if (si_2) { // 512, 256, ..., 4, 2 SI family
		if ((i == 0) && (result & 1) == 0) // S0 cannot be 0 if SI==4
			return 0;

		result |= si | 0xC00; // si == 1 << i
	} else { // 1536, 768, ..., 6, 3 SI family
		result |= (1 << i) | ((so >> i) & 0x3) << 10;
	}

	return result;
}

static inline void print_alloc_array(alloc_desc const desc[], size_t count)
{
	static char const *fams[] = { " 12K", " 11K", "POW2", "NONE" };
	size_t i;

	for (i = 0; i < count; ++i) {
		alloc_desc const *d = &desc[i];
		uint8_t fam = d->family < 4 ? d->family : 3;
		uint8_t adj_fam = d->adj_family < 4 ? d->adj_family : 3;

		dbg_inf("%p CH:%03u PR:%06u TP:%02u SD:0x%.3X SI:%02d SO:%02u SL/SW:%02u "
				"FAM:%s ADJFAM:%s ISO:%u ADJFREQ:%06u%s%s\n",
				d,
				d->ch->cn,
				get_presence_rate_hz(d->ch->pr),
				d->ch->tp,
				d->sd,
				d->si,
				d->so,
				d->sw,
				fams[fam],
				fams[adj_fam],
				d->is_iso,
				d->adj_pr_freq,
				d->has_longest_sl ? ", Longest SL" : "",
				d->has_max_freq ? ", Max Freq." : "");
	};
}

static inline void print_desc(alloc_desc const *desc)
{
	print_alloc_array(desc, 1);
}

static inline void print_sorted_alloc_array(alloc_desc const *desc[],
		size_t count)
{
	size_t i;

	for (i = 0; i < count; ++i)
		print_desc(desc[i]);
}

static void print_slots(uint16_t slots[], size_t count)
{
	size_t i, j;
	size_t const columns = 48;

	for (i = 0; i < count / columns; ++i) {
		for (j = 0; j < columns; ++j) {
			uint16_t c = slots[i * columns + j];

			if (c < 256)
				printf("%.2X ", c & 0xFF);
			else if (c == SF_MAPPING_EMPTY_SLOT)
				printf("-- ");
			else if (c == SF_MAPPING_CONTROL_SLOT)
				printf("CS ");
			else if (c == SF_MAPPING_COLLISION)
				printf("XX ");
			else
				printf("?? ");
		}
		printf("\n");
	}

	printf("\n");
}

static void print_channels_table(alloc_desc const *desc[],
		size_t rows, size_t cols)
{
	size_t i, j;

	for (i = 0; i < rows; ++i) {
		//printf("row %u: ", i);
		for (j = 0; j < cols; ++j) {
			//printf("%p ", desc[i * cols + j]);
			if (desc[i * cols + j])
				printf("%.3u ", desc[i * cols + j]->ch->cn);
			else
				printf("nil ");
		}

		printf("\n");
	}
}

static inline channel_desc *get_channel(channels_map *map, uint8_t cn)
{
	return &map->channels[cn];
}

channel_desc const *channels_map_get_channel(channels_map const *map,
		uint8_t cn)
{
	return get_channel((channels_map *)map, cn);
}

static inline channel_desc *get_channel_committed(channels_map *map,
		uint8_t cn)
{
	return &map->channels[CSMI_MAX_CHANNELS + cn];
}

channel_desc const *channels_map_get_channel_committed(
		channels_map const *map, uint8_t cn)
{
	return get_channel_committed((channels_map *)map, cn);
}

void channels_map_clear_slots(channels_map *map)
{
	uint16_t i;

	for (i = 0; i < CSMI_SLOTS_PER_SUPERFRAME; ++i)
		map->slots[i] = SF_MAPPING_EMPTY_SLOT;
}

void channels_map_init(channels_map *map)
{
	map->rf = 0;
	map->cg = 0;
	map->sm = 0;
	map->mapping_collisions_count = 0;

	memset(map->channels, 0, sizeof(map->channels));
	channels_map_clear_slots(map);
}

uint32_t channels_map_define_channel(channels_map *map,
		channel_desc const *ch)
{
	channel_desc *channel = get_channel(map, ch->cn);
	channel_desc const *chc = get_channel_committed(map, ch->cn);

	if (ch->cn >= CSMI_MAX_CHANNELS)
		return EINVAL;

	memcpy(channel, ch, sizeof(channel_desc));

	if (compare_channels(ch, chc)) {
		channel->state = CH_STATE_TO_BE_DEFINED;
		return EOK;
	}

	if (compare_channels_content(ch, chc)) {
		channel->state = CH_STATE_CONTENT_CHANGED;
		return EOK;
	}

	channel->state = CH_STATE_PRESENT;

	return EOK;
}

void channels_map_remove_channel(channels_map *map, uint8_t cn)
{
	channel_desc *channel = get_channel(map, cn);
	channel_desc const *chc = get_channel_committed(map, cn);

	if (chc->state == CH_STATE_PRESENT) {
		channel->state = CH_STATE_TO_BE_REMOVED;
		return;
	}

	if (channel->state == CH_STATE_FREE) {
		dbg_warn("Channel %u not found.\n", cn);
		return;
	}

	channel->state = CH_STATE_FREE;
}

void channels_map_commit_changes(channels_map *map)
{
	size_t const size = sizeof(map->channels) / 2;
	size_t i;

	for (i = 0; i < CSMI_MAX_CHANNELS; ++i) {
		channel_desc *new = get_channel(map, i);
		channel_desc const *old = get_channel_committed(map, i);

		if (new->state == CH_STATE_TO_BE_REMOVED)
			new->state = CH_STATE_FREE;
		else if(new->state == CH_STATE_TO_BE_DEFINED)
			new->state = CH_STATE_PRESENT;
		else if(new->state == CH_STATE_CONTENT_CHANGED)
			new->state = CH_STATE_PRESENT;
		else if (new->state == old->state)
			continue;
		else
			dbg_warn("Warning. Unknown state 0x%.2X.\n", new->state);
	}

	memcpy(map->channels + CSMI_MAX_CHANNELS, map->channels, size);
}

void channels_map_undo_changes(channels_map *map)
{
	static size_t const size = sizeof(map->channels) / 2;

	memcpy(map->channels, map->channels + CSMI_MAX_CHANNELS, size);
}

uint32_t channels_map_validate_and_setup(channels_map *map)
{
	uint16_t i, j, k;
	uint16_t channels_count = 0;

	uint16_t clk_gear = map->cg;

	// Array with channel allocation descriptors and result allocation map
	// (that itself contains mentioned array).
	static alloc_desc channels[CSMI_MAX_CHANNELS];
	static alloc_desc *sorted_alloc_array[CSMI_MAX_CHANNELS];
	static alloc_desc *pending_alloc_table[CSMI_MAX_CHANNELS];

	// Index of channel with highest freq. rate
	uint16_t max_freq_ch_index = 0;
	// Highest freq. rate (in Hz)
	uint32_t max_freq_hz = 0;
	// Adjusted highest freq. rate
	uint32_t adj_highest_freq_rate = 0;
	// Index of channel with longest sample width
	uint16_t longest_sample_chan_index = 0;
	// Longest sample width (in slots)
	uint8_t longest_sample_slot_width = 0;
	// PR family of highest freq. rate channel
	channel_pr_family max_freq_pr_fam;

	dbg_inf("Initializing Channels allocation array\n");

	memset(channels, 0, sizeof(channels));

	/*
	 * Initializing Channels allocation array and finding the one with:
	 *	 a) highest freq.
	 *	 b) longest sample width
	 *	 c) get list and number of all used Channels
	 */
	for (i = 0; i < CSMI_MAX_CHANNELS; ++i) {
		channel_desc *ch = get_channel(map, i);
		uint32_t freq_hz;

		if (ch->state == CH_STATE_FREE || ch->state == CH_STATE_TO_BE_REMOVED)
			continue;

		channels[channels_count++].ch = ch;

		freq_hz = get_presence_rate_hz(ch->pr);

		if (freq_hz == 0) {
			dbg_err("Invalid PR for Channel %u\n", ch->cn);

			return EINVAL;
		}

		if (freq_hz > max_freq_hz) {
			max_freq_ch_index = i;
			max_freq_hz = freq_hz;
			max_freq_pr_fam = GET_PRESENCE_RATE_FAM(ch->pr);

			if (max_freq_pr_fam == CH_PR_FAM_MUL_11025) {
				max_freq_pr_fam = CH_PR_FAM_MUL_12K;
				compute_pr_from_freq(max_freq_hz,
						max_freq_pr_fam,
						false,
						&adj_highest_freq_rate);
			} else {
				adj_highest_freq_rate = max_freq_hz;
			}
		}

		if (ch->sl > longest_sample_slot_width) {
			longest_sample_chan_index = i;
			longest_sample_slot_width = ch->sl;
		}
	}

	dbg_inf("%u Channels found.\n", channels_count);

	for (i = 0; i < channels_count; ++i) {
		channels[i].has_longest_sl = i == longest_sample_chan_index;
		channels[i].has_max_freq = i == max_freq_ch_index;
		channel_desc const *ch = channels[i].ch;

		dbg_tmp("CH:%.3u PR:%.6u TP:%.2u SL:%.2u%s%s\n",
				ch->cn,
				get_presence_rate_hz(ch->pr),
				ch->tp,
				ch->sl,
				channels[i].has_longest_sl ? ", Longest SL" : "",
				channels[i].has_max_freq ? ", Max Freq." : "");
	}

	if (channels_count == 0)
		return EOK;

	dbg_inf("Selecting ISO mode.\n");

	// Choosing Channel mode between ISO and NON-ISO
	for (i = 0; i < channels_count; ++i) {
		channel_desc *ch = channels[i].ch;
		channel_pr_family pr_family = GET_PRESENCE_RATE_FAM(ch->pr);

		channels[i].family = pr_family;

		if (pr_family == CH_PR_FAM_MUL_11025)
			pr_family = CH_PR_FAM_MUL_12K;

		channels[i].ch = ch;
		channels[i].sw = ch->sl;
		channels[i].adj_family = pr_family;
		channels[i].is_iso = (pr_family == max_freq_pr_fam)
			&& (ch->force_iso == CH_FORCE_ISO_NONE);
	}

	print_alloc_array(channels, channels_count);

	dbg_inf("Adjusting PR frequencies.\n");

	// Two values of channels' adjusted PR frequencies - min. and max. ones
	uint32_t min_adj_pr_freq = MAX_PR_FREQ;
	uint32_t max_adj_pr_freq = MIN_PR_FREQ;

	for (i = 0; i < channels_count; ++i) {
		alloc_desc *desc = &channels[i];
		bool select_larger = max_freq_pr_fam != desc->family;
		uint32_t freq_rate = get_presence_rate_hz(desc->ch->pr);

		compute_pr_from_freq(freq_rate, max_freq_pr_fam, select_larger,
				&desc->adj_pr_freq);
		dbg_tmp("Adjusting Presence Rate for Channel %u from %u to %u\n",
				desc->ch->cn,
				freq_rate,
				desc->adj_pr_freq);

		desc->sw = desc->ch->sl + (desc->is_iso ? 0 : 1);
		dbg_tmp("Setting Segment Width (SW/SL) to %u\n", desc->sw);

		if (desc->adj_pr_freq < min_adj_pr_freq)
			min_adj_pr_freq = desc->adj_pr_freq;

		if (desc->adj_pr_freq > max_adj_pr_freq)
			max_adj_pr_freq = desc->adj_pr_freq;
	}

	print_alloc_array(channels, channels_count);

	dbg_inf("Max Presence Rate: %u, Min Presence Rate: %u\n",
			max_adj_pr_freq, min_adj_pr_freq);

	dbg_inf("Calculating Data Width.\n");

	// Flag that indicates whether Channel with longest sample is ISO or not
	bool is_longest_iso = channels[longest_sample_chan_index].is_iso;

	// Subframe width, message width and channel data width (expressed in slots)
	uint8_t subframe_width_val;
	uint8_t control_width_val;
	uint8_t data_width_val;

	if (max_freq_pr_fam == CH_PR_FAM_MUL_12K) {
		// MUL_12K family: 2/8 : width <= 24bits (20bits for NISO), 8/32 otherwise

		// WIDTH IN CONDITIONS IS EXPRESSED IN SLOTS!!!

		if (longest_sample_slot_width <= (is_longest_iso ? 6 : 5)) {
			subframe_width_val = 8;
			control_width_val = 2;
		} else {
			subframe_width_val = 32;
			control_width_val = 8;
		}
	} else {
		// POW_2 family: 2/6 : width <= 16bits (12bits for NISO), 6/24 otherwise

		if (longest_sample_slot_width <= (is_longest_iso ? 4 : 3)) {
			subframe_width_val = 6;
			control_width_val = 2;
		} else {
			subframe_width_val = 24;
			control_width_val = 6;
		}
	}

	data_width_val = subframe_width_val - control_width_val;

	dbg_inf("Data Width set to %u Slots (SW: %u, CW: %u).\n",
			data_width_val, subframe_width_val, control_width_val);

	// ######## 4) Allocating channels ########

	dbg_inf("Allocating channels.\n");

	uint16_t table_height = max_adj_pr_freq / min_adj_pr_freq;
	uint16_t table_width = channels_count;

	size_t const table_size = table_height * table_width
		* sizeof(alloc_desc **);

	dbg_tmp("Creating 2 tables %ux%u\n", table_width, table_height);
	dbg_inf("Requesting %lu bytes for init_alloc_table\n", table_size);

	alloc_desc **init_alloc_table = (alloc_desc **)malloc_(table_size);

	if (!init_alloc_table) {
		dbg_err("Failed to allocate memory. Requested %lu bytes.\n",
				table_size);

		return ENOMEM;
	}

	dbg_inf("Requesting %lu bytes for alloc_table\n", table_size);

	alloc_desc **alloc_table = (alloc_desc **) malloc_(table_size);

	if (!alloc_table) {
		dbg_err("Failed to allocate memory. Requested %lu bytes.\n",
				table_size);
		free_(init_alloc_table);

		return ENOMEM;
	}

	dbg_inf("Initializing init_alloc_table\n");

	for (i = 0; i < table_height * table_width; ++i)
		init_alloc_table[i] = NULL;

	// Sorting channels

	dbg_inf("Preparing for sorting channels.\n");

	// Array with sorted channels descriptors
	for (i = 0; i < channels_count; ++i) {
		sorted_alloc_array[i] = &channels[i];
		dbg_tmp("sorted_alloc_array[%u] = %p\n", i, sorted_alloc_array[i]);
	}

	dbg_inf("Sorting Channels by PR frequency.\n");

	sort(sorted_alloc_array, channels_count, sizeof(alloc_desc *),
			compare_by_adj_pr_freq_desc);

	bool const preallocate_only = true;
	uint16_t preallocated_count = 0;

	dbg_tmp("Sorted channels:\n");
	print_sorted_alloc_array(sorted_alloc_array, channels_count);

	// Writing channels to the array
	for (i = 0; i < channels_count; ++i) {
		alloc_desc *desc = sorted_alloc_array[i];
		uint16_t const row_increment = max_adj_pr_freq / desc->adj_pr_freq;

		if (preallocate_only
				&& i > 0
				&& desc->adj_pr_freq < sorted_alloc_array[0]->adj_pr_freq) {
			break;
		}

		//min_adj_pr_freq / max_adj_pr_freq

		for (j = 0; j < table_height; j += row_increment) {
			uint16_t column_idx = 0;

			while (init_alloc_table[j * table_width + column_idx])
				++column_idx;

			init_alloc_table[j * table_width + column_idx] = desc;
		}

		++preallocated_count;
	}

	dbg_tmp("init_alloc_table:\n");
	print_channels_table(init_alloc_table, table_height, table_width);

	// Array with sorted channels descriptors that were not allocated yet
	// ######## WORKAROUND FOR SORTING ONLY PART OF ARRAY ########
	uint16_t pending_channels_count = channels_count - preallocated_count;

	// Filling pending array
	for (i = 0; i < pending_channels_count; ++i) {
		dbg_tmp("pending_alloc_table[%u] = %p\n",
				i, sorted_alloc_array[i + preallocated_count]);
		pending_alloc_table[i] = sorted_alloc_array[i + preallocated_count];
	}

	// Sorting remaining channels
	if (pending_channels_count) {
		dbg_inf("Sorting remaining Channels by PR frequency.\n");
		sort(pending_alloc_table,
				pending_channels_count,
				sizeof(pending_alloc_table[0]),
				compare_by_adj_pr_freq_desc);
	}

	// Writing descriptors back to original array
	for (i = 0; i < pending_channels_count; ++i) {
		sorted_alloc_array[i + preallocated_count] = pending_alloc_table[i];
	}

	// .....

	dbg_inf("Initializing Channels allocation table.\n");

	for (i = 0; i < table_height; ++i) {
		for (j = 0; j < table_width; ++j) {
			alloc_table[i * table_width + j]
				= init_alloc_table[i * table_width + j];
		}
	}

	dbg_tmp("alloc_table:\n");
	print_channels_table(alloc_table, table_height, table_width);

	dbg_inf("Requesting %lu bytes for row_slot_width_sum table.\n",
			table_height * sizeof(uint16_t));

	uint16_t *row_slot_width_sum = (uint16_t *)malloc_(
			table_height * sizeof(uint16_t));

	if (!row_slot_width_sum) {
		dbg_err("Failed to allocate memory. Requested %lu bytes.\n",
				table_height * sizeof(uint16_t));

		free_(init_alloc_table);
		free_(alloc_table);

		return ENOMEM;
	}

	uint32_t fastest_pr_freq = channels[max_freq_ch_index].adj_pr_freq;
	uint16_t allocated_count = preallocated_count;
	uint16_t alloc_iter_counter = 0;
	uint16_t max_row_slot_width = 0;

	dbg_inf("\nAllocating Channels. Preallocated: %u, Remaining: %u\n",
			allocated_count, channels_count - allocated_count);

	// Channel allocation iterations
	while (allocated_count < channels_count && alloc_iter_counter < 1) {
		dbg_inf("Allocating Channel %u\n",
				sorted_alloc_array[allocated_count]->ch->cn);
		// Copying initial channels alignment (from pre-allocation)
		if (alloc_iter_counter > 0) {
			for (i = 0; i < table_height; ++i) {
				for (j = 0; j < table_width; ++j) {
					dbg_tmp("copying %p from init_alloc_table to alloc_table\n",
							alloc_table[i * table_width + j]);
					alloc_table[i * table_width + j]
						= init_alloc_table[i * table_width + j];
				}
			}
		}

		dbg_tmp("alloc_table:\n");
		print_channels_table(alloc_table, table_height, table_width);

		dbg_inf("Copied initial Channels alignment\n");

		// Next iteration of allocation
		for (k = allocated_count; k < channels_count; ++k) {
			alloc_desc *desc = sorted_alloc_array[k];

			uint32_t chan_freq = desc->adj_pr_freq;
			uint16_t freq_div = fastest_pr_freq / chan_freq;
			uint16_t best_offset = 0;
			uint16_t min_row_slot_width = UINT16_MAX;
			uint16_t offset;
			uint16_t row;

			// Trying all possible offsets and storing
			for (offset = 0; offset < freq_div; ++offset) {
				// Counting bit width of each single row
				max_row_slot_width = 0;

				for (i = 0; i < table_height; ++i) {
					row_slot_width_sum[i] = 0;

					for (j = 0; j < table_width; ++j) {
						if (alloc_table[i * table_width + j])
							row_slot_width_sum[i]
								+= alloc_table[i * table_width + j]->sw;
					}

					if ((i - offset) % freq_div == 0)
						row_slot_width_sum[i] += desc->sw;

					if (row_slot_width_sum[i] > max_row_slot_width) {
						max_row_slot_width = row_slot_width_sum[i];
					}
				}

				if (max_row_slot_width < min_row_slot_width) {
					best_offset = offset;
					min_row_slot_width = max_row_slot_width;
				}
			}

			for (row = best_offset; row < table_height; row += freq_div) {
				uint16_t column_idx = 0;

				while (column_idx < table_width
						&& alloc_table[row * table_width + column_idx]) {
					++column_idx;
				}

				if (column_idx < table_width) {
					alloc_table[row * table_width + column_idx] = desc;
				}
			}
		}

		dbg_inf("Counting bit width of each single row.\n");

		// Counting bit width of each single row
		max_row_slot_width = 0;

		for (i = 0; i < table_height; ++i) {
			row_slot_width_sum[i] = 0;

			for (j = 0; j < table_width; ++j)
				if (alloc_table[i * table_width + j])
					row_slot_width_sum[i]
						+= alloc_table[i * table_width + j]->sw;

			if (row_slot_width_sum[i] > max_row_slot_width) {
				max_row_slot_width = row_slot_width_sum[i];
			}
		}

		++alloc_iter_counter;
	}

	free_(init_alloc_table);

	// ######## Optionally fixing maximum row width to fit in Subframe ########
	// 241

	// Row repacking table (contains sub-row index, 0 is base one)
	size_t const repack_rows_table_size
		= table_height * table_width * sizeof(uint16_t);

	dbg_inf("Requesting %lu bytes for repack_rows_table.\n",
			repack_rows_table_size);

	uint16_t const INVALID_ROW = 0xFFFF;
	uint16_t *repack_rows_table = (uint16_t *)malloc_(repack_rows_table_size);

	if (!repack_rows_table) {
		dbg_err("Failed to allocate memory. Requested %lu bytes.\n",
				repack_rows_table_size);

		free_(alloc_table);
		free_(row_slot_width_sum);

		return ENOMEM;
	}

	// Initializing array
	for (i = 0; i < table_height; ++i) {
		for (j = 0; j < table_width; ++j) {
			repack_rows_table[i * table_width + j] = INVALID_ROW;
		}
	}

	// Processing each row
	uint16_t max_subrow_index = 0;
	uint16_t new_max_row_width = 0;

	dbg_tmp("table_height: %u, table_width: %u\n", table_height, table_width);

	for (i = 0; i < table_height; ++i) {
		uint16_t subrow_index = 0;
		uint16_t data_width_sum = 0;
		uint16_t max_row_width = 0;

		dbg_tmp("Processing row: %u\n", i);

		for (j = 0; j < table_width; ++j) {
			alloc_desc *desc = alloc_table[i * table_width + j];

			if (!desc)
				continue;

			//dbg_tmp("Processing Channel %u.\n", desc->ch->cn);
			print_desc(desc);

			uint16_t chan_data_width = desc->sw;

			//dbg_tmp("chan_data_width: %u, data_width_sum: %u, data_width_val: %u\n",
					//chan_data_width, data_width_sum, data_width_val);

			if (data_width_sum + chan_data_width > data_width_val) {
				++subrow_index;
				//dbg_tmp("subrow_index: %u\n", subrow_index);
				data_width_sum = 0;

				if (max_row_width > new_max_row_width)
					new_max_row_width = max_row_width;

				max_row_width = 0;
			} else {
				++max_row_width;
				//dbg_tmp("max_row_width: %u\n", max_row_width);
			}

			data_width_sum += chan_data_width;

			repack_rows_table[i * table_width + j] = subrow_index;
		}

		dbg_tmp("subrow_index: %u, data_width_sum: %u, max_row_width: %u\n",
				subrow_index, data_width_sum, max_row_width);

		if (max_row_width > new_max_row_width)
			new_max_row_width = max_row_width;

		if (subrow_index > max_subrow_index)
			max_subrow_index = subrow_index;
	}

	dbg_tmp("alloc_table:\n");
	print_channels_table(alloc_table, table_height, table_width);

	uint8_t rows_div_factor = 0;
	uint8_t rounded_subrows_count = 0;

	while ((1 << rows_div_factor) < (max_subrow_index + 1))
		++rows_div_factor;

	rounded_subrows_count = 1 << rows_div_factor;

	dbg_inf("Starting Clock Gear computation loop.\n");

	// #### Clock Gear computation loop ####

	for (i = 0; i < 10; ++i) {
		uint32_t const clk_freq_rate = get_root_freq_hz(map->rf);
		// Current Clock Gear value
		uint32_t const clk_gear_div = 1 << (10 - clk_gear);
		// Current bus freq.  (related to BITS)
		uint32_t const bus_freq = clk_freq_rate / clk_gear_div;

		// Computing initial Segment Interval and freq. family taking
		// fastest Channel

		dbg_inf("Trying Clock Gear %u.\n", clk_gear);

		channel_pr_family si_family = CH_PR_FAM_NONE;
		uint32_t adjusted_si = 0;
		compute_seg_int(bus_freq, adj_highest_freq_rate, &si_family,
				&adjusted_si);

		// Denotes row multiplicity between two Subframes with two consecutive
		// samples of the highest PR channel
		uint16_t const highest_pr_rows_mul = adjusted_si / subframe_width_val;

		// Storing Segment Intervals for channels
		for (j = 0; j < channels_count; ++j) {
			channels[j].si = adjusted_si * max_adj_pr_freq
				/ channels[j].adj_pr_freq;
		}

		dbg_tmp("rounded_subrows_count: %lu, highest_pr_rows_mul: %lu\n",
				rounded_subrows_count, highest_pr_rows_mul);

		// Checking whether current alignment can be implemented
		// (number of sub-rows inserted must be lower or equal to
		// empty Subframes (as initial SI for fastest channel shows)
		if (rounded_subrows_count > highest_pr_rows_mul) {
			if (clk_gear < 10) {
				++clk_gear;
				continue;
			} else {
				dbg_err("Failed to find proper Clock Gear.\n");

				free_(alloc_table);
				free_(row_slot_width_sum);
				free_(repack_rows_table);

				return EINVAL;
			}
		}
	}

	dbg_inf("Selected Clock Gear: %u\n", clk_gear);
	dbg_tmp("Max Sub-row index: %lu\n", max_subrow_index);

	if (max_subrow_index) {
		uint16_t col_index = 0;
		uint16_t new_table_height = table_height * rounded_subrows_count;

		dbg_inf("Repacking table after dividing into sub-rows.\n");

		size_t const new_alloc_table_size = new_table_height
			* new_max_row_width
			* sizeof(alloc_desc **);

		dbg_inf("Requesting %lu bytes for new_alloc_table\n",
				new_alloc_table_size);

		dbg_tmp("Allocating new_alloc_table\n");
		alloc_desc **new_alloc_table
			= (alloc_desc **)malloc_(new_alloc_table_size);

		if (!new_alloc_table) {
			dbg_err("Failed to allocate memory. Requested %lu bytes.\n",
					new_alloc_table_size);

			free_(alloc_table);
			free_(row_slot_width_sum);
			free_(repack_rows_table);

			return ENOMEM;
		}

		dbg_tmp("new_alloc_table_size: %u rows, %u cols\n",
				new_table_height, new_max_row_width);

		for (i = 0; i < new_alloc_table_size / sizeof(alloc_desc **); ++i)
			new_alloc_table[i] = NULL;

		for (i = 0; i < table_height; ++i) {
			col_index = 0;

			uint16_t row_index = rounded_subrows_count * i;
			uint16_t subrow_index = 0;

			for (j = 0; j < table_width; ++j) {
				subrow_index = repack_rows_table[i * table_width + j];

				if (subrow_index == INVALID_ROW) {
					dbg_tmp("Invalid row index %u\n", subrow_index);
					break;
				}

				if (subrow_index > repack_rows_table[i * table_width + j - 1])
					col_index = 0;

				alloc_desc *desc = alloc_table[i * table_width + j];

				if (desc) {
					new_alloc_table[
						(row_index + subrow_index) * table_width + col_index]
						= desc;
				}

				if (++col_index > new_max_row_width) {
					free_(alloc_table);
					free_(row_slot_width_sum);
					free_(repack_rows_table);
					free_(new_alloc_table);

					return EINVAL;
				}
			}
		}

		table_height = new_table_height;
		table_width = new_max_row_width;

		dbg_tmp("Releasing alloc_table\n");
		free_(alloc_table);

		dbg_tmp("Replacing alloc_table with new_alloc_table\n");
		alloc_table = new_alloc_table;

		dbg_tmp("new_alloc_table:\n");
		print_channels_table(new_alloc_table, table_height, table_width);
	}

	dbg_tmp("Releasing repack_rows_table\n");
	free_(repack_rows_table);

	dbg_tmp("Recalculating maximum row width.\n");

	// ######## Recalculating maximum row width (in slots) ########

	uint16_t *tmp = (uint16_t *)realloc_(row_slot_width_sum,
			table_height * sizeof(uint16_t));

	if (!row_slot_width_sum) {
		dbg_err("Failed to allocate memory. Requested %lu bytes.\n",
				table_height * sizeof(uint16_t));

		free_(row_slot_width_sum);
		free_(alloc_table);
		free_(tmp);

		return ENOMEM;
	}

	row_slot_width_sum = tmp;
	max_row_slot_width = 0;

	dbg_inf("Calculating maximum Slot Width sum.\n");

	print_channels_table(alloc_table, table_height, table_width);

	for (i = 0; i < table_height; ++i) {
		row_slot_width_sum[i] = 0;

		for (j = 0; j < table_width; ++j) {
			if (!alloc_table[i * table_width + j])
				continue;

			row_slot_width_sum[i] += alloc_table[i * table_width + j]->sw;
		}

		if (row_slot_width_sum[i] > max_row_slot_width) {
			max_row_slot_width = row_slot_width_sum[i];
		}
	}

	dbg_tmp("Releasing row_slot_width_sum\n");
	free_(row_slot_width_sum);

	dbg_tmp("Maximum Slot Width is %u\n", max_row_slot_width);

	// ######## Storing Segment Offsets ########

	dbg_inf("Storing Segment Offsets.\n");

	uint16_t seg_offset = 0;

	for (i = 0; i < table_height; ++i) {
		uint16_t row_seg_offset = seg_offset + control_width_val;

		for (j = 0; j < table_width; ++j) {
			alloc_desc *desc = alloc_table[i * table_width + j];

			if (!desc)
				break;

			desc->so = row_seg_offset;
			desc->sd = compute_segment_dist(desc->si, row_seg_offset);

			if (desc->sd == 0) {
				dbg_err("Invalid Segment Distribution 0x%.4X\n", desc->sd);

				free_(alloc_table);

				return EINVAL;
			}

			row_seg_offset += desc->sw;
		}

		seg_offset += subframe_width_val;
	}

	dbg_tmp("Releasing alloc_table\n");
	free_(alloc_table);

	if (!subframe_modes_get_subframe_mode_val(&map->sm,
				subframe_width_val, control_width_val)) {
		dbg_err("Failed to obtain Subframe Mode for "
				"%u Control Slots and %u Data Slots.\n",
				control_width_val,
				subframe_width_val);
		return EINVAL;
	}

	map->cg = clk_gear;

	// Check for collisions

	dbg_tmp("Checking for collisions.\n");

	for (i = 0; i < CSMI_SLOTS_PER_SUPERFRAME; ++i) {
		uint16_t slot_index = i % subframe_width_val;

		map->slots[i] = (slot_index < control_width_val)
			? SF_MAPPING_CONTROL_SLOT
			: SF_MAPPING_EMPTY_SLOT;
	}

	map->mapping_collisions_count = 0;

	for (i = 0; i < channels_count; ++i) {
		alloc_desc const *desc = &channels[i];

		uint16_t si = desc->si;
		uint16_t offs = desc->so;
		uint16_t sw = desc->sw;

		dbg_tmp("CH:%u, SI:%u, SO:%u, SW:%u\n", desc->ch->cn, si, offs, sw);

		while (offs < CSMI_SLOTS_PER_SUPERFRAME) {
			for (j = 0; j < sw && offs < CSMI_SLOTS_PER_SUPERFRAME; ++j) {
				if (map->slots[offs] != SF_MAPPING_EMPTY_SLOT) {
					map->slots[offs] = SF_MAPPING_COLLISION;
					++map->mapping_collisions_count;
				} else {
					map->slots[offs] = SF_MAPPING_CHANNEL(desc->ch->cn);
				}

				++offs;
			}

			if (si <= sw) {
				dbg_err("SI <= SW!\n");
				break;
			}

			offs += si - sw;
		}
	}

	dbg_tmp("Displaying assigned Slots:\n");
	print_slots(map->slots, CSMI_SLOTS_PER_SUPERFRAME);

	if (map->mapping_collisions_count) {
		dbg_err("Failed to allocate Channels. Collisions count: %u\n",
				map->mapping_collisions_count);
		return EINVAL;
	}

	dbg_tmp("No collisions found.\n");
	dbg_inf("Updating Channels Allocation Map.\n");

	for (i = 0; i < channels_count; ++i) {
		channel_desc *ch = channels[i].ch;
		channel_desc const *chc = get_channel_committed(map, ch->cn);

		dbg_inf("Updating Channel %u.\n", ch->cn);

		if (ch->force_iso == CH_FORCE_ISO_PUSHED) {
			ch->tp = CSMI_TP_PUSHED;
		} else if (ch->force_iso == CH_FORCE_ISO_PULLED) {
			ch->tp = CSMI_TP_PULLED;
		} else {
			ch->tp = channels[i].is_iso
				? CSMI_TP_ISOCHRONOUS
				: CSMI_TP_PUSHED;
		}

		ch->sd = channels[i].sd;
		ch->sl = channels[i].sw;

		// Update Channel's state

		if (compare_channels(ch, chc)) {
			ch->state = CH_STATE_TO_BE_DEFINED;
			continue;
		}

		if (compare_channels_content(ch, chc)) {
			ch->state = CH_STATE_CONTENT_CHANGED;
			continue;
		}

		ch->state = CH_STATE_PRESENT;
	}

	return EOK;
}

