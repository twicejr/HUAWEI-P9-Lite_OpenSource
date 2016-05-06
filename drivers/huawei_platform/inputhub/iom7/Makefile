# qindiwen 20120625 begin

# InputHub Driver
obj-$(CONFIG_INPUTHUB)		+= inputhub_bridge.o
obj-$(CONFIG_INPUTHUB)		+= inputhub_route.o
obj-$(CONFIG_INPUTHUB)		+= sensor_info.o
obj-$(CONFIG_INPUTHUB)       += sensorhub_logbuff.o
obj-$(CONFIG_INPUTHUB)       += sensor_debug.o

obj-$(CONFIG_INPUTHUB)	+= sensorhub_channel.o
obj-$(CONFIG_INPUTHUB)  += motionhub_channel.o
#obj-$(CONFIG_INPUTHUB)	+= touch_events_channel.o

obj-$(CONFIG_INPUTHUB)  += sensor_sys_info.o
# qindiwen 20120625 end

ifdef CONFIG_HISI_BB
obj-$(CONFIG_INPUTHUB)  += rdr_sensorhub.o
endif