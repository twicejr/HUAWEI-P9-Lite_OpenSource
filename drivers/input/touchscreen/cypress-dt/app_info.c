#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/list.h>
#include <linux/export.h>
#include <linux/app_info.h>
#include <linux/slab.h>

struct info_node
{
    char name[APP_INFO_NAME_LENTH];
    char value[APP_INFO_VALUE_LENTH];
    struct list_head entry;
};

static LIST_HEAD(app_info_list);
static DEFINE_SPINLOCK(app_info_list_lock);

int app_info_set(const char * name, const char * value)
{
    struct info_node *new_node;
    int name_lenth = strlen(name);
    int value_lenth = strlen(value);

    if(WARN_ON(!name || !value))
        return -1;

    new_node = kzalloc(sizeof(*new_node), GFP_KERNEL);
    if(new_node == NULL)
    {
        return -1;
    }

    memcpy(new_node->name,name,((name_lenth > (APP_INFO_NAME_LENTH-1))?(APP_INFO_NAME_LENTH-1):name_lenth));
    memcpy(new_node->value,value,((value_lenth > (APP_INFO_VALUE_LENTH-1))?(APP_INFO_VALUE_LENTH-1):value_lenth));

    spin_lock(&app_info_list_lock);
    list_add_tail(&new_node->entry,&app_info_list);
    spin_unlock(&app_info_list_lock);

    return 0;
}

EXPORT_SYMBOL(app_info_set);


static int app_info_proc_show(struct seq_file *m, void *v)
{
    struct info_node *node;

    list_for_each_entry(node,&app_info_list,entry)
    {
        seq_printf(m,"%-32s:%32s\n",node->name,node->value);
    }
    return 0;
}

static int app_info_proc_open(struct inode *inode, struct file *file)
{
    return single_open(file, app_info_proc_show, NULL);
}

static const struct file_operations app_info_proc_fops =
{
    .open		= app_info_proc_open,
    .read		= seq_read,
    .llseek		= seq_lseek,
    .release	= single_release,
};

static int __init proc_app_info_init(void)
{
    proc_create("app_info", 0, NULL, &app_info_proc_fops);
    return 0;
}

//module_init(proc_app_info_init);
