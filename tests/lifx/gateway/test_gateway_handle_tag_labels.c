#include <string.h>

#include "gateway.c"

#include "test_gateway_utils.h"

int
main(void)
{
    lgtd_lifx_wire_load_packet_infos_map();

    struct lgtd_lifx_gateway gw;
    memset(&gw, 0, sizeof(gw));

    struct lgtd_lifx_packet_header hdr;
    memset(&hdr, 0, sizeof(hdr));

    struct lgtd_lifx_packet_tag_labels pkt = {
        .label = "test", .tags = 0
    };

    lgtd_lifx_gateway_handle_tag_labels(&gw, &hdr, &pkt);
    if (gw.tag_ids != 0) {
        errx(1, "expected gw.tags == 0 but got %jx", (uintmax_t)gw.tags);
    }

    pkt.tags = TAG_ID_TO_VALUE(42);
    lgtd_lifx_gateway_handle_tag_labels(&gw, &hdr, &pkt);
    if (gw.tag_ids != TAG_ID_TO_VALUE(42)) {
        errx(
            1, "expected gw.tags == %jx but got %jx",
            TAG_ID_TO_VALUE(42), (uintmax_t)gw.tags
        );
    }
    if (!gw.tags[42]) {
        errx(1, "tag_id 42 should have been set");
    }
    if (strcmp(gw.tags[42]->label, pkt.label)) {
        errx(
            1, "unexpected label %.*s (expected %s)",
            (int)sizeof(gw.tags[0]->label), gw.tags[42]->label, pkt.label
        );
    }

    strcpy(pkt.label, "toto");
    pkt.tags = TAG_ID_TO_VALUE(2) | TAG_ID_TO_VALUE(4);
    lgtd_lifx_gateway_handle_tag_labels(&gw, &hdr, &pkt);
    memset(&pkt, 0, sizeof(pkt));
    lgtd_lifx_gateway_handle_tag_labels(&gw, &hdr, &pkt);
    uint64_t expected;
    expected = TAG_ID_TO_VALUE(42) | TAG_ID_TO_VALUE(2) | TAG_ID_TO_VALUE(4);
    if (gw.tag_ids != expected) {
        errx(
            1, "expected gw.tags == %jx but got %jx",
            TAG_ID_TO_VALUE(42), (uintmax_t)gw.tags
        );
    }
    if (strcmp(gw.tags[2]->label, "toto")) {
        errx(
            1, "unexpected label %.*s (expected %s)",
            (int)sizeof(gw.tags[0]->label), gw.tags[2]->label, "toto"
        );
    }
    if (strcmp(gw.tags[4]->label, "toto")) {
        errx(
            1, "unexpected label %.*s (expected %s)",
            (int)sizeof(gw.tags[0]->label), gw.tags[4]->label, "toto"
        );
    }
    if (strcmp(gw.tags[42]->label, "test")) {
        errx(
            1, "unexpected label %.*s (expected %s)",
            (int)sizeof(gw.tags[0]->label), gw.tags[42]->label, "test"
        );
    }

    return 0;
}