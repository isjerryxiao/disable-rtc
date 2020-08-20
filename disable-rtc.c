#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/rtc.h>

MODULE_AUTHOR("Jerry Xiao");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Disable rtc device");

static char *devname = "rtc0";

module_param(devname, charp, 0000);
MODULE_PARM_DESC(devname, "rct device name");

static const struct rtc_class_ops *ops;

static int __init lkm_init(void)
{
	struct rtc_device *rtc;
    if (!(rtc = rtc_class_open(devname)))
        return -ENODEV;
    ops = rtc->ops;
    rtc->ops = NULL;

    return 0;
}

static void __exit lkm_exit(void)
{
	struct rtc_device *rtc;
    if (!(rtc = rtc_class_open(devname)))
        {return;}
    if (rtc->ops == NULL)
        rtc->ops = ops;
}

module_init(lkm_init);
module_exit(lkm_exit);
