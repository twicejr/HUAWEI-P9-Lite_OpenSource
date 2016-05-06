#ifndef CSMI_AUX_H_
# define CSMI_AUX_H_

# include <cdn_stdint.h>

# define CSMI_SLOTS_PER_SUPERFRAME 1536
# define CSMI_MAX_CHANNEL_NUMBER 15
# define CSMI_MAX_CHANNELS (CSMI_MAX_CHANNEL_NUMBER + 1)

/**
 * Channel State.
 */
typedef enum {
	/** Channel is not used. */
	CH_STATE_FREE,
	/** Channel and its Content is present in SLIMbus configuration.
	 * No need for any changes. */
	CH_STATE_PRESENT,
	/** Channel and its Content need to be added to SLIMbus. */
	CH_STATE_TO_BE_DEFINED,
	/** Channel need to be removed from SLIMbus. */
	CH_STATE_TO_BE_REMOVED,
	/** Content of the Channel has changed. */
	CH_STATE_CONTENT_CHANGED
} channel_state;

/**
 * Channel mode force flag
 */
typedef enum {
	CH_FORCE_ISO_NONE,
	CH_FORCE_ISO_PUSHED,
	CH_FORCE_ISO_PULLED
} force_chan_iso;

/**
 * Converts sample size from bits per sample to Slots per sample.
 * Number of bits per sample should be multiple of 4, otherwise the resulting
 * value will be rounded down to nearest multiple of 4.
 */
# define GET_CH_SEGMENT_LENGTH(SAMPLE_SIZE_BITS_) \
	((SAMPLE_SIZE_BITS_) >> 2)

/**
 * SLIMbus Data Channel and its Content definition structure.
 * Values of the fields matches those defined in csmi.h.
 * @field[in] cn Channel Number.
 *		This value is defined by user while defining Channel.
 * @field[out] sd Segment Distribution.
 *		This value is calculated by Channel allocation algorithm.
 * @field[inout] tp Transport Protocol.
 *		This value is defined by user while defining Channel.
 *		In some cases this value can be changed by Channel allocation
 *		algorithm.
 * @field[inout] sl Segment Length measured in Slots.
 *		This value is defined by user while defining Channel.
 *		GET_CH_SEGMENT_LENGTH macro can be used to convert bits per sample to
 *		Slots per sample. Channel allocation algorithm can increase this value
 *		in some cases by one depending on the selected Transport Protocol.
 * @field[in] fl Frequency Locked flag.
 *		This value is defined by user while defining Channel.
 * @field[in] pr Presence Rate.
 *		This value is defined by user while defining Channel.
 * @field[in] af Auxiliary Bit Format.
 *		This value is defined by user while defining Channel.
 * @field[in] cl Channel Link flag.
 *		This value is defined by user while defining Channel.
 * @field[in] dt Data Type.
 *		This value is defined by user while defining Channel.
 * @field[in] dl Data Length.
 *		This value is defined by user while defining Channel.
 * @field force_iso Force Isochronous mode: PUSHED, PULLED or ISO
 *		This value is defined by user while defining Channel.
 * @field[out] state State of the Channel.
 *		This value is set internally by Channel allocation algorithm.
 *		Depending on its value user shall send appropriate messages to the
 *		SLIMbus Manager.
 */
typedef struct {
	uint8_t cn; // 8 bits
	uint16_t sd; // 12 bits
	uint8_t tp; // 4 bits
	uint8_t sl; // 5 bits
	uint8_t state; // 3 bits

	uint8_t fl; // 1 bits
	uint8_t pr; // 7 bits
	uint8_t af; // 4 bits
	uint8_t cl; // 1 bit
	uint8_t dt; // 4 bits
	uint8_t dl; // 5 bits
	uint8_t force_iso; // 1 - bit
} channel_desc;

/**
 * Channels allocation map.
 * @field rf Root Frequency (expressed in Hertz).
 * @field cg Clock gear value.
 * @field sm Subframe Mode
 * @field channels Array with Channel descriptors and their backup.
 * @field slots Array with exact channels mapping within superframe.
 *	  Each array value denotes single slot.
 *	  Value mapping:
 *		SF_MAPPING_EMPTY_SLOT	: Empty slot
 *		SF_MAPPING_CONTROL_SLOT : Control slot
 *		SF_MAPPING_COLLISION	: Collision (sample overlaps another sample
 *		   or control area)
 *		SF_MAPPING_CHANNEL(n)	: Slot occupied by n-th Channel.
 *	  This array is for internal use only.
 * @field mapping_collisions_count Number of Slot collisions while mapping
 *	  channels. This field is for internal use only.
 */
typedef struct {
	uint8_t rf; // 4 bits
	uint8_t cg; // 4 bits
	uint8_t sm; // 5 bits

	channel_desc channels[CSMI_MAX_CHANNELS * 2];
	uint16_t slots[CSMI_SLOTS_PER_SUPERFRAME];
	uint16_t mapping_collisions_count;
} channels_map;

/**
 * Sets all slots to empty.
 */
void channels_map_clear_slots(channels_map *map);

/**
 * Initializes Channels Map.
 * This function can be also called to clear defined configurations.
 * @param[in] map Pointer to Channels Map.
 */
void channels_map_init(channels_map *map);

/**
 * Creates new or update Channel config and defines its content.
 * @param[in] map Pointer to Channels Map.
 * @param[in] ch Channel definition.
 * @returns EOK on success.
 * @returns EINVAL if Channel has invalid configuration.
 */
uint32_t channels_map_define_channel(channels_map *map, channel_desc const *ch);
/**
 * Removes Channel from map.
 * @param[in] map Pointer to Channels Map.
 * @param[in] ch Number of the Channel that needs to be removed.
 * @returns EINVAL if there is no specified Channel.
 */
void channels_map_remove_channel(channels_map *map, uint8_t cn);
/**
 * Commits current configuration. Must be called after all SLIMbus messages
 * are successfully sent to SLIMbus.
 * @param[in] map Pointer to Channels Map.
 * @param[in] ch Number of the Channel to be removed.
 */
void channels_map_commit_changes(channels_map *map);

/**
 * Cancels all changes made to the Channels Map and restores Channels
 * configuration from committed version.
 * @param[in] map Pointer to Channels Map.
 */
void channels_map_undo_changes(channels_map *map);

/**
 * Tries to allocate and adjust Channels with given configuration. This
 * function modify, if needed, only Clock Gear and Subframe Mode.
 * I will set up Segment Distribution and Segment Length in Channel
 * definitions. Also, in some cases, it can modify the Transport Protocol.
 * @param[in] map Pointer to Channels Map.
 * @returns EOK if Specified Channels setup can be done in SLIMbus.
 * @returns EINVALID if configurations is invalid or given Channels setup
 * cannot be done in SLIMbus.
 */

uint32_t channels_map_validate_and_setup(channels_map *map);
/**
 * Returns pointer to Channel structure from current setup with given
 * Channel Number.
 * @param[in] map Pointer to Channels Map.
 * @param[in] cn Number of the requested Channel.
 * @returns EOK on success.
 * @returns EINVALID if given Channel does not exist.
 */
channel_desc const *channels_map_get_channel(channels_map const *map,
		uint8_t cn);

/**
 * Returns pointer to Channel structure from committed setup with given
 * Channel Number.
 * @param[in] map Pointer to Channels Map.
 * @param[in] cn Number of the requested Channel.
 * @returns EOK on success.
 * @returns EINVALID if given Channel does not exist.
 */
channel_desc const *channels_map_get_channel_committed(
		channels_map const *map, uint8_t cn);

#endif

