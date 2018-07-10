/*
 * linux/drivers/cpufreq/cpufreq_powersave.c
 *
 * Copyright (C) 2002 - 2003 Dominik Brodowski <linux@brodo.de>
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/cpufreq.h>
#include <linux/init.h>
#include <linux/module.h>

static void cpufreq_gov_powersave2_limits(struct cpufreq_policy *policy)
{
	pr_debug("setting to %u kHz\n", policy->min);
	__cpufreq_driver_target(policy, policy->min, CPUFREQ_RELATION_L);
}

static struct cpufreq_governor cpufreq_gov_powersave2 = {
	.name		= "powersave",
	.limits		= cpufreq_gov_powersave2_limits,
	.owner		= THIS_MODULE,
};

static int __init cpufreq_gov_powersave2_init(void)
{
	return cpufreq_register_governor(&cpufreq_gov_powersave2);
}

static void __exit cpufreq_gov_powersave2_exit(void)
{
	cpufreq_unregister_governor(&cpufreq_gov_powersave2);
}

MODULE_LICENSE("GPL");

module_init(cpufreq_gov_powersave2_init);
module_exit(cpufreq_gov_powersave2_exit);
