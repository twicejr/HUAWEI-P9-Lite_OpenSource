/*
 * huawei Hisuite mode usb function
 * 1. Setting APP set this state;
 * 2. PC Hisuite get this state;
 * 3. If it is hisuite mode, PC Hisuite will autorun.
 */

static int suitestate = 0xff;

static ssize_t suitestate_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    return sprintf(buf, "%d\n", suitestate);
}
static ssize_t suitestate_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t size)
{
    int value;
    if(sscanf(buf, "%d", &value) == 1)
    {
        suitestate = value;
        return size;
    }
    return -1;
}

static DEVICE_ATTR(suitestate, S_IRUGO | S_IWUSR, suitestate_show, suitestate_store);

int get_suitestate(void)
{
    return suitestate;
}
