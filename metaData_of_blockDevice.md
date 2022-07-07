function to get metadata of block device's partition:
```
void __init printk_all_partitions(void)
{
	struct class_dev_iter iter;
	struct device *dev;

	class_dev_iter_init(&iter, &block_class, NULL, &disk_type);
	while ((dev = class_dev_iter_next(&iter))) {
		struct gendisk *disk = dev_to_disk(dev);
		struct block_device *part;
		char devt_buf[BDEVT_SIZE];
		unsigned long idx;

		/*
		 * Don't show empty devices or things that have been
		 * suppressed
		 */
		if (get_capacity(disk) == 0 || (disk->flags & GENHD_FL_HIDDEN))
			continue;

		/*
		 * Note, unlike /proc/partitions, I am showing the numbers in
		 * hex - the same format as the root= option takes.
		 */
		rcu_read_lock();
		xa_for_each(&disk->part_tbl, idx, part) {
			if (!bdev_nr_sectors(part))
				continue;
			printk("%s%s %10llu %pg %s",
			       bdev_is_partition(part) ? "  " : "",
			       bdevt_str(part->bd_dev, devt_buf),
			       bdev_nr_sectors(part) >> 1, part,
			       part->bd_meta_info ?
					part->bd_meta_info->uuid : "");
			if (bdev_is_partition(part))
				printk("\n");
			else if (dev->parent && dev->parent->driver)
				printk(" driver: %s\n",
					dev->parent->driver->name);
			else
				printk(" (driver?)\n");
		}
		rcu_read_unlock();
	}
	class_dev_iter_exit(&iter);
}
```
> but this function is already decleared in genhd.h header file. So there is no need to define it.

## By following next steps, we'll get our metadata

### Step-1: add header file to kernel module
```
#include<linux/genhd.h>
```
### Step-2: Call the function
```
__init printk_all_partitions()
```
> it'll show all partition's information in blockDevice


