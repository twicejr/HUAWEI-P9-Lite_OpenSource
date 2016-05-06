struct clk;

void __sp804_clockevents_init(void __iomem *, unsigned int,
			      struct clk *, const char *);
static inline void sp804_clockevents_init(void __iomem *base, unsigned int irq, const char *name)
{
	__sp804_clockevents_init(base, irq, NULL, name);

}
