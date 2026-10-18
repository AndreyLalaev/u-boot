// SPDX-License-Identifier: GPL-2.0+

#include <image.h>
#include "imagetool.h"

/* magic: 'B' 'L' '3' '3' */
#define HEADER_MAGIC cpu_to_be32(0x424c3333)

struct milkv_duo_header {
	uint32_t jump0;
	uint32_t magic;
	uint32_t cksum;
	uint32_t size;
	uint64_t runaddr;
	uint32_t reserved1;
	uint32_t reserved2;
};

static struct milkv_duo_header milkv_duo_header;

static uint32_t milkvimage_calc_chksum(struct stat *sbuf) {
	// TODO
	return 0;
}

static int milkvimage_verify_header(unsigned char *ptr, int image_size, struct image_tool_params *params) {
	struct milkv_duo_header *hdr = (struct milkv_duo_header *)ptr;
	if (hdr->magic != HEADER_MAGIC)
		return -1;

	return 0;
}
static void milkvimage_print_header(const void *ptr, struct image_tool_params *params) {
	printf("printing header\n");
}
static void milkvimage_set_header(void *ptr, struct stat *sbuf, int ifd, struct image_tool_params *params) {
	struct milkv_duo_header *hdr = (struct milkv_duo_header *)ptr;

	hdr->jump0 = 0;
	hdr->magic = HEADER_MAGIC;
	hdr->cksum = milkvimage_calc_chksum(sbuf);
	hdr->size = cpu_to_le32((uint32_t)sbuf->st_size + sizeof(*hdr));
	hdr->runaddr = cpu_to_le32(params->addr);
	hdr->reserved1 = 0;
	hdr->reserved2 = 0;
}

static int milkvimage_check_image_type(uint8_t type)
{
	if (type == IH_TYPE_MILKVIMAGE)
		return EXIT_SUCCESS;
	else
		return EXIT_FAILURE;
}

U_BOOT_IMAGE_TYPE(
	milkvimage,
	"Milk-V Duo Image Support",
	sizeof(struct milkv_duo_header),
	&milkv_duo_header,
	NULL,
	milkvimage_verify_header,
	milkvimage_print_header,
	milkvimage_set_header,
	NULL,
	milkvimage_check_image_type,
	NULL,
	NULL);
