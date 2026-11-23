/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _FALLOC_H_
#define _FALLOC_H_

#include <uapi/linux/falloc.h>


/*
 * Space reservation ioctls and argument structure
 * are designed to be compatible with the legacy XFS ioctls.
 *
 * Keep them kernel-only: host tools such as scripts/asn1_compiler are built
 * with -I$(srctree)/include, so glibc's <bits/fcntl-linux.h> (which does
 * #include <linux/falloc.h> when __USE_GNU is set) ends up here instead of
 * the exported UAPI header.  There __s16/__s32/__s64/__u32 and _IOW are not
 * defined, and the struct is of no use to user space anyway - it only needs
 * the FALLOC_FL_* flags from <uapi/linux/falloc.h> above.
 */
#ifdef __KERNEL__
struct space_resv {
	__s16		l_type;
	__s16		l_whence;
	__s64		l_start;
	__s64		l_len;		/* len == 0 means until end of file */
	__s32		l_sysid;
	__u32		l_pid;
	__s32		l_pad[4];	/* reserved area */
};

#define FS_IOC_RESVSP		_IOW('X', 40, struct space_resv)
#define FS_IOC_RESVSP64		_IOW('X', 42, struct space_resv)
#endif /* __KERNEL__ */

#define	FALLOC_FL_SUPPORTED_MASK	(FALLOC_FL_KEEP_SIZE |		\
					 FALLOC_FL_PUNCH_HOLE |		\
					 FALLOC_FL_COLLAPSE_RANGE |	\
					 FALLOC_FL_ZERO_RANGE |		\
					 FALLOC_FL_INSERT_RANGE |	\
					 FALLOC_FL_UNSHARE_RANGE)

#endif /* _FALLOC_H_ */
