
// This is a TensorFlow Lite model file that has been converted into a C data
// array using the tensorflow.lite.util.convert_bytes_to_c_source() function.
// This form is useful for compiling into a binary for devices that don't have a
// file system.


// We need to keep the data array aligned on some architectures.
#ifdef __has_attribute
#define HAVE_ATTRIBUTE(x) __has_attribute(x)
#else
#define HAVE_ATTRIBUTE(x) 0
#endif
#if HAVE_ATTRIBUTE(aligned) || (defined(__GNUC__) && !defined(__clang__))
#define DATA_ALIGN_ATTRIBUTE __attribute__((aligned(4)))
#else
#define DATA_ALIGN_ATTRIBUTE
#endif

const unsigned char g_model[] DATA_ALIGN_ATTRIBUTE = {
    0x20, 0x00, 0x00, 0x00, 0x54, 0x46, 0x4c, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x12, 0x00, 0x1c, 0x00, 0x18, 0x00, 0x14, 0x00, 0x10, 0x00, 0x0c, 0x00,
    0x08, 0x00, 0x00, 0x00, 0x04, 0x00, 0x12, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00,
    0x00, 0x48, 0x00, 0x00, 0x00, 0xf4, 0x04, 0x00, 0x00, 0x18, 0x05, 0x00, 0x00,
    0x54, 0x0d, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0c,
    0x00, 0x00, 0x00, 0x08, 0x00, 0x0c, 0x00, 0x08, 0x00, 0x04, 0x00, 0x08, 0x00,
    0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00,
    0x00, 0x6d, 0x69, 0x6e, 0x5f, 0x72, 0x75, 0x6e, 0x74, 0x69, 0x6d, 0x65, 0x5f,
    0x76, 0x65, 0x72, 0x73, 0x69, 0x6f, 0x6e, 0x00, 0x0e, 0x00, 0x00, 0x00, 0xa8,
    0x04, 0x00, 0x00, 0x9c, 0x04, 0x00, 0x00, 0x94, 0x04, 0x00, 0x00, 0x8c, 0x04,
    0x00, 0x00, 0x74, 0x04, 0x00, 0x00, 0x7c, 0x03, 0x00, 0x00, 0x2c, 0x03, 0x00,
    0x00, 0x24, 0x03, 0x00, 0x00, 0x34, 0x02, 0x00, 0x00, 0x24, 0x01, 0x00, 0x00,
    0x1c, 0x01, 0x00, 0x00, 0x2c, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x04,
    0x00, 0x00, 0x00, 0x94, 0xfb, 0xff, 0xff, 0xbe, 0xfb, 0xff, 0xff, 0x04, 0x00,
    0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x21, 0xa2, 0x8c, 0xc9, 0x5f, 0x1d, 0xce,
    0x41, 0x9f, 0xcd, 0x20, 0xb1, 0xdf, 0x53, 0x2f, 0x81, 0xda, 0xfb, 0xff, 0xff,
    0x04, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0xe2, 0x4f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x7b, 0x5f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x08, 0x00, 0x08, 0x00,
    0x08, 0x00, 0x08, 0x00, 0x08, 0x00, 0x08, 0x00, 0x08, 0x00, 0x08, 0x00, 0x08,
    0x00, 0x08, 0x00, 0x08, 0x00, 0x08, 0x00, 0x08, 0x00, 0x08, 0x00, 0x08, 0x00,
    0x08, 0x00, 0x08, 0x00, 0x08, 0x00, 0x08, 0x00, 0x08, 0x00, 0x08, 0x00, 0x08,
    0x00, 0x08, 0x00, 0x08, 0x00, 0x08, 0x00, 0x08, 0x00, 0x08, 0x00, 0x08, 0x00,
    0x08, 0x00, 0x08, 0x00, 0x08, 0x0d, 0x00, 0x0d, 0x00, 0x0d, 0x00, 0x0d, 0x00,
    0x0d, 0x00, 0x0d, 0x00, 0x0d, 0x00, 0x0d, 0x00, 0x0d, 0x00, 0x0d, 0x00, 0x0d,
    0x00, 0x0d, 0x00, 0x0d, 0x00, 0x0d, 0x00, 0x0d, 0x00, 0x0d, 0x00, 0xa0, 0xfc,
    0xff, 0xff, 0xca, 0xfc, 0xff, 0xff, 0x04, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x00, 0xee, 0xfc, 0x00, 0xec, 0x05, 0x16, 0xef, 0xec, 0xe6, 0xf8, 0x03, 0x01,
    0x00, 0xfa, 0xf8, 0xf5, 0xda, 0xeb, 0x27, 0x14, 0xef, 0xde, 0xe2, 0xda, 0xf0,
    0xdf, 0x32, 0x06, 0x01, 0xe6, 0xee, 0xf9, 0x00, 0x16, 0x07, 0xe0, 0xfe, 0xff,
    0xe9, 0x05, 0xe7, 0xef, 0x81, 0x1b, 0x18, 0xea, 0xca, 0x01, 0x0f, 0x00, 0xdb,
    0xf7, 0x0e, 0xec, 0x12, 0x1e, 0x04, 0x13, 0xb2, 0xe7, 0xfd, 0x06, 0xbb, 0xe0,
    0x0c, 0xec, 0xf0, 0xdf, 0xeb, 0xf7, 0x05, 0x26, 0x19, 0xe4, 0x70, 0x1a, 0xea,
    0x1e, 0x34, 0xdf, 0x19, 0xf3, 0xf1, 0x19, 0x0e, 0x03, 0x1b, 0xe1, 0xde, 0x13,
    0xf6, 0x19, 0xff, 0xf6, 0x1a, 0x17, 0xf1, 0x1c, 0xdb, 0x1a, 0x1a, 0x20, 0xe6,
    0x19, 0xf5, 0xff, 0x97, 0x0b, 0x00, 0x00, 0xce, 0xdf, 0x0d, 0xf7, 0x15, 0xe4,
    0xed, 0xfc, 0x0d, 0xe9, 0xfb, 0xec, 0x5c, 0xfc, 0x1d, 0x02, 0x58, 0xe3, 0xe0,
    0xf4, 0x15, 0xec, 0xf9, 0x00, 0x13, 0x05, 0xec, 0x0c, 0x1c, 0x14, 0x0c, 0xe9,
    0x0a, 0xf4, 0x18, 0x00, 0xd7, 0x05, 0x27, 0x02, 0x15, 0xea, 0xea, 0x02, 0x9b,
    0x00, 0x0c, 0xfa, 0xe9, 0xea, 0xfe, 0x01, 0x14, 0xfd, 0x0b, 0x02, 0xf0, 0xef,
    0x06, 0xee, 0x01, 0x0d, 0x06, 0xe7, 0xf7, 0x11, 0xf5, 0x0a, 0xf9, 0xf1, 0x23,
    0xff, 0x0d, 0xf2, 0xec, 0x11, 0x26, 0x1d, 0xf2, 0xea, 0x28, 0x18, 0xe0, 0xfb,
    0xf3, 0xf4, 0x05, 0x1c, 0x1d, 0xfb, 0xfd, 0x1e, 0xfc, 0x11, 0xe8, 0x06, 0x09,
    0x03, 0x12, 0xf2, 0x35, 0xfb, 0xdd, 0x1b, 0xf9, 0xef, 0xf3, 0xe7, 0x6f, 0x0c,
    0x1d, 0x00, 0x43, 0xfd, 0x0d, 0xf1, 0x0a, 0x19, 0x1a, 0xfa, 0xe0, 0x18, 0x1e,
    0x13, 0x37, 0x1c, 0x12, 0xec, 0x3a, 0x0c, 0xb6, 0xcb, 0xe6, 0x13, 0xf7, 0xeb,
    0xf1, 0x05, 0x1b, 0xfa, 0x19, 0xe5, 0xec, 0xcf, 0x0c, 0xf4, 0xd6, 0xfd, 0xff,
    0xff, 0x04, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00,
    0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xff, 0xff, 0x80, 0xca, 0xfc, 0xb3, 0x1f, 0x9e, 0xe5, 0xb2, 0x3d, 0x33, 0x80,
    0x24, 0xeb, 0xc9, 0xaf, 0x32, 0x68, 0x05, 0x21, 0xc8, 0xc6, 0xf7, 0xc8, 0x37,
    0x80, 0x0e, 0xa3, 0x5a, 0xa8, 0x73, 0x9a, 0x95, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x87, 0x6b, 0x87, 0x6b, 0x87, 0x6b, 0x87, 0x6b, 0x87, 0x6b, 0x87, 0x6b,
    0x87, 0x6b, 0x87, 0x6b, 0x87, 0x6b, 0x87, 0x6b, 0x87, 0x6b, 0x87, 0x6b, 0x87,
    0x6b, 0x87, 0x6b, 0x87, 0x6b, 0x87, 0x6b, 0x41, 0x2d, 0x41, 0x2d, 0x41, 0x2d,
    0x41, 0x2d, 0x41, 0x2d, 0x41, 0x2d, 0x41, 0x2d, 0x41, 0x2d, 0x41, 0x2d, 0x41,
    0x2d, 0x41, 0x2d, 0x41, 0x2d, 0x41, 0x2d, 0x41, 0x2d, 0x41, 0x2d, 0x41, 0x2d,
    0xbf, 0xd2, 0xbf, 0xd2, 0xbf, 0xd2, 0xbf, 0xd2, 0xbf, 0xd2, 0xbf, 0xd2, 0xbf,
    0xd2, 0xbf, 0xd2, 0xbf, 0xd2, 0xbf, 0xd2, 0xbf, 0xd2, 0xbf, 0xd2, 0xbf, 0xd2,
    0xbf, 0xd2, 0xbf, 0xd2, 0xbf, 0xd2, 0x0c, 0x00, 0x0c, 0x00, 0x0c, 0x00, 0x0c,
    0x00, 0x0c, 0x00, 0x0c, 0x00, 0x0c, 0x00, 0x0c, 0x00, 0x0c, 0x00, 0x0c, 0x00,
    0x0c, 0x00, 0x0c, 0x00, 0x0c, 0x00, 0x0c, 0x00, 0x0c, 0x00, 0x0c, 0x00, 0x9c,
    0xfe, 0xff, 0xff, 0xc6, 0xfe, 0xff, 0xff, 0x04, 0x00, 0x00, 0x00, 0x40, 0x00,
    0x00, 0x00, 0x73, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00,
    0x00, 0xe1, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x81, 0x00, 0x00, 0x00,
    0xa5, 0x00, 0x00, 0x00, 0x43, 0x00, 0x00, 0x00, 0xfe, 0x00, 0x00, 0x00, 0xd5,
    0x00, 0x00, 0x00, 0xd5, 0x00, 0x00, 0x00, 0xb2, 0x00, 0x00, 0x00, 0x60, 0x00,
    0x00, 0x00, 0x77, 0x00, 0x00, 0x00, 0x19, 0x00, 0x00, 0x00, 0xdf, 0x00, 0x00,
    0x00, 0x12, 0xff, 0xff, 0xff, 0x04, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff,
    0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00,
    0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x81, 0x39, 0x51, 0x19, 0xc7, 0xfe, 0x80,
    0xf0, 0x1c, 0x12, 0x80, 0xc0, 0x80, 0xd2, 0x1b, 0x27, 0x00, 0xff, 0x80, 0xea,
    0x67, 0x0b, 0x00, 0xd9, 0x92, 0x37, 0x74, 0x30, 0xd5, 0xfc, 0x80, 0xef, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x47, 0x3e, 0x47, 0x3e, 0x47, 0x3e, 0x47,
    0x3e, 0x47, 0x3e, 0x47, 0x3e, 0x47, 0x3e, 0x47, 0x3e, 0x47, 0x3e, 0x47, 0x3e,
    0x47, 0x3e, 0x47, 0x3e, 0x47, 0x3e, 0x47, 0x3e, 0x47, 0x3e, 0x47, 0x00, 0x40,
    0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00,
    0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40,
    0x00, 0x40, 0x00, 0x40, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00,
    0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xc0,
    0x00, 0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x0d, 0x00, 0x0d,
    0x00, 0x0d, 0x00, 0x0d, 0x00, 0x0d, 0x00, 0x0d, 0x00, 0x0d, 0x00, 0x0d, 0x00,
    0x0d, 0x00, 0x0d, 0x00, 0x0d, 0x00, 0x0d, 0x00, 0x0d, 0x00, 0x0d, 0x00, 0x0d,
    0x00, 0x0d, 0x00, 0x00, 0x00, 0x06, 0x00, 0x08, 0x00, 0x04, 0x00, 0x06, 0x00,
    0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x31, 0x2e, 0x35,
    0x2e, 0x30, 0x00, 0x00, 0x00, 0xf4, 0xff, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xff,
    0xfc, 0xff, 0xff, 0xff, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x00, 0x00, 0x21,
    0x00, 0x00, 0x00, 0x54, 0x4f, 0x43, 0x4f, 0x20, 0x43, 0x6f, 0x6e, 0x76, 0x65,
    0x72, 0x74, 0x65, 0x64, 0x2e, 0x20, 0x2b, 0x20, 0x58, 0x4d, 0x4f, 0x53, 0x20,
    0x6f, 0x70, 0x74, 0x69, 0x6d, 0x69, 0x7a, 0x65, 0x64, 0x2e, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x3c, 0xf8, 0xff, 0xff, 0x10,
    0x00, 0x00, 0x00, 0x64, 0x02, 0x00, 0x00, 0x68, 0x02, 0x00, 0x00, 0x6c, 0x02,
    0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0xf0, 0x01, 0x00, 0x00, 0x8c, 0x01, 0x00,
    0x00, 0x14, 0x01, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x58, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x98, 0xfe, 0xff, 0xff, 0x10, 0x00, 0x00, 0x00, 0x38,
    0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x26, 0x00,
    0x00, 0x00, 0x70, 0x61, 0x72, 0x00, 0x74, 0x68, 0x00, 0x63, 0x67, 0x00, 0x02,
    0x00, 0x00, 0x04, 0x04, 0x01, 0x05, 0x28, 0x02, 0x0c, 0x10, 0x02, 0x01, 0x02,
    0x08, 0x01, 0x28, 0x04, 0x01, 0x1d, 0x01, 0x01, 0x01, 0x09, 0x24, 0x02, 0x24,
    0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x88, 0xfe, 0xff, 0xff, 0x0c, 0x00, 0x00,
    0x00, 0x44, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00, 0x35, 0x00, 0x00, 0x00,
    0x70, 0x61, 0x72, 0x00, 0x74, 0x68, 0x00, 0x63, 0x67, 0x00, 0x02, 0x00, 0x00,
    0x04, 0x04, 0x01, 0x05, 0x28, 0x02, 0x0c, 0x10, 0x02, 0x01, 0x02, 0x08, 0x01,
    0x28, 0x04, 0x6d, 0x65, 0x6d, 0x00, 0x02, 0x00, 0x10, 0x00, 0xe0, 0x00, 0x05,
    0x05, 0x02, 0x0d, 0x2a, 0x02, 0x01, 0x02, 0x0c, 0x17, 0x29, 0x24, 0x04, 0x24,
    0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x03,
    0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x0a, 0x00,
    0x00, 0x00, 0x4c, 0xff, 0xff, 0xff, 0x10, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00,
    0x00, 0x3c, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x26, 0x00, 0x00, 0x00,
    0x70, 0x61, 0x72, 0x00, 0x74, 0x68, 0x00, 0x63, 0x67, 0x00, 0x02, 0x00, 0x0f,
    0x04, 0x04, 0x01, 0x05, 0x28, 0x02, 0x0c, 0x10, 0x02, 0x01, 0x02, 0x08, 0x01,
    0x28, 0x04, 0x01, 0x1d, 0x01, 0x01, 0x01, 0x09, 0x24, 0x02, 0x24, 0x01, 0x00,
    0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x09, 0x00, 0x00, 0x00, 0x3c, 0xff, 0xff, 0xff, 0x0c, 0x00, 0x00, 0x00, 0x44,
    0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00, 0x35, 0x00, 0x00, 0x00, 0x70, 0x61,
    0x72, 0x00, 0x74, 0x68, 0x00, 0x63, 0x67, 0x00, 0x02, 0x00, 0x0f, 0x04, 0x04,
    0x01, 0x05, 0x28, 0x02, 0x0c, 0x10, 0x02, 0x01, 0x02, 0x08, 0x01, 0x28, 0x04,
    0x6d, 0x65, 0x6d, 0x00, 0x02, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x05, 0x05, 0x02,
    0x0d, 0x2a, 0x02, 0x01, 0x02, 0x0c, 0x17, 0x29, 0x24, 0x04, 0x24, 0x01, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00,
    0x00, 0x02, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00,
    0x10, 0x00, 0x14, 0x00, 0x10, 0x00, 0x0c, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x04, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x38, 0x00,
    0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x26, 0x00, 0x00,
    0x00, 0x70, 0x61, 0x72, 0x00, 0x74, 0x68, 0x00, 0x63, 0x67, 0x00, 0x02, 0x00,
    0x0f, 0x04, 0x04, 0x01, 0x05, 0x28, 0x02, 0x0c, 0x10, 0x02, 0x01, 0x02, 0x08,
    0x01, 0x28, 0x04, 0x01, 0x1d, 0x01, 0x01, 0x01, 0x09, 0x24, 0x02, 0x24, 0x01,
    0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
    0x00, 0x06, 0x00, 0x00, 0x00, 0x10, 0x00, 0x10, 0x00, 0x00, 0x00, 0x0c, 0x00,
    0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x10, 0x00, 0x00, 0x00, 0x0c,
    0x00, 0x00, 0x00, 0x44, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00, 0x35, 0x00,
    0x00, 0x00, 0x70, 0x61, 0x72, 0x00, 0x74, 0x68, 0x00, 0x63, 0x67, 0x00, 0x02,
    0x00, 0x0f, 0x04, 0x04, 0x01, 0x05, 0x28, 0x02, 0x0c, 0x10, 0x02, 0x01, 0x02,
    0x08, 0x01, 0x28, 0x04, 0x6d, 0x65, 0x6d, 0x00, 0x02, 0x00, 0x40, 0x00, 0xe0,
    0x00, 0x05, 0x05, 0x02, 0x0d, 0x2a, 0x02, 0x01, 0x02, 0x0c, 0x17, 0x29, 0x24,
    0x04, 0x24, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00,
    0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x00, 0x2c, 0x05,
    0x00, 0x00, 0xa4, 0x04, 0x00, 0x00, 0x24, 0x04, 0x00, 0x00, 0x8c, 0x03, 0x00,
    0x00, 0x38, 0x03, 0x00, 0x00, 0xe4, 0x02, 0x00, 0x00, 0x4c, 0x02, 0x00, 0x00,
    0xf8, 0x01, 0x00, 0x00, 0xb0, 0x01, 0x00, 0x00, 0x28, 0x01, 0x00, 0x00, 0xd4,
    0x00, 0x00, 0x00, 0x8c, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x16, 0xfb,
    0xff, 0xff, 0x14, 0x00, 0x00, 0x00, 0x4c, 0x00, 0x00, 0x00, 0x0d, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x07, 0x64, 0x00, 0x00, 0x00, 0xce, 0xfd, 0xff, 0xff,
    0x00, 0x00, 0x00, 0x01, 0x10, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x1c,
    0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x1a, 0xde, 0x0a,
    0x38, 0x01, 0x00, 0x00, 0x00, 0x66, 0x64, 0x87, 0x3f, 0x01, 0x00, 0x00, 0x00,
    0x13, 0x42, 0x8d, 0xbf, 0x1c, 0x00, 0x00, 0x00, 0x58, 0x43, 0x5f, 0x66, 0x63,
    0x5f, 0x64, 0x65, 0x65, 0x70, 0x69, 0x6e, 0x5f, 0x61, 0x6e, 0x79, 0x6f, 0x75,
    0x74, 0x5f, 0x32, 0x2f, 0x6f, 0x75, 0x74, 0x70, 0x75, 0x74, 0x00, 0x00, 0x00,
    0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x7c, 0xfd, 0xff, 0xff, 0x10, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x09, 0x28, 0x00, 0x00, 0x00, 0x1d, 0x00, 0x00, 0x00, 0x58, 0x43,
    0x5f, 0x66, 0x63, 0x5f, 0x64, 0x65, 0x65, 0x70, 0x69, 0x6e, 0x5f, 0x61, 0x6e,
    0x79, 0x6f, 0x75, 0x74, 0x5f, 0x32, 0x2f, 0x77, 0x65, 0x69, 0x67, 0x68, 0x74,
    0x73, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x10,
    0x00, 0x00, 0x00, 0xc0, 0xfd, 0xff, 0xff, 0x10, 0x00, 0x00, 0x00, 0x0b, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x30, 0x00, 0x00, 0x00, 0x26, 0x00, 0x00,
    0x00, 0x58, 0x43, 0x5f, 0x66, 0x63, 0x5f, 0x64, 0x65, 0x65, 0x70, 0x69, 0x6e,
    0x5f, 0x61, 0x6e, 0x79, 0x6f, 0x75, 0x74, 0x5f, 0x32, 0x2f, 0x62, 0x69, 0x61,
    0x73, 0x5f, 0x73, 0x68, 0x69, 0x66, 0x74, 0x5f, 0x73, 0x63, 0x61, 0x6c, 0x65,
    0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00,
    0x00, 0x10, 0x00, 0x00, 0x00, 0x2e, 0xfc, 0xff, 0xff, 0x14, 0x00, 0x00, 0x00,
    0x4c, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x64,
    0x00, 0x00, 0x00, 0xe6, 0xfe, 0xff, 0xff, 0x00, 0x00, 0x00, 0x01, 0x10, 0x00,
    0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00,
    0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0x01, 0x00, 0x00, 0x00, 0xaa, 0x7b, 0xbe, 0x37, 0x01, 0x00, 0x00, 0x00, 0x2e,
    0xbd, 0xbd, 0x3f, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00,
    0x00, 0x00, 0x58, 0x43, 0x5f, 0x66, 0x63, 0x5f, 0x64, 0x65, 0x65, 0x70, 0x69,
    0x6e, 0x5f, 0x61, 0x6e, 0x79, 0x6f, 0x75, 0x74, 0x5f, 0x31, 0x2f, 0x6f, 0x75,
    0x74, 0x70, 0x75, 0x74, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x94, 0xfe, 0xff, 0xff, 0x10, 0x00,
    0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x28, 0x00, 0x00,
    0x00, 0x1d, 0x00, 0x00, 0x00, 0x58, 0x43, 0x5f, 0x66, 0x63, 0x5f, 0x64, 0x65,
    0x65, 0x70, 0x69, 0x6e, 0x5f, 0x61, 0x6e, 0x79, 0x6f, 0x75, 0x74, 0x5f, 0x31,
    0x2f, 0x77, 0x65, 0x69, 0x67, 0x68, 0x74, 0x73, 0x00, 0x00, 0x00, 0x02, 0x00,
    0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0xd8, 0xfe, 0xff,
    0xff, 0x10, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07,
    0x30, 0x00, 0x00, 0x00, 0x26, 0x00, 0x00, 0x00, 0x58, 0x43, 0x5f, 0x66, 0x63,
    0x5f, 0x64, 0x65, 0x65, 0x70, 0x69, 0x6e, 0x5f, 0x61, 0x6e, 0x79, 0x6f, 0x75,
    0x74, 0x5f, 0x31, 0x2f, 0x62, 0x69, 0x61, 0x73, 0x5f, 0x73, 0x68, 0x69, 0x66,
    0x74, 0x5f, 0x73, 0x63, 0x61, 0x6c, 0x65, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x46,
    0xfd, 0xff, 0xff, 0x24, 0x00, 0x00, 0x00, 0x5c, 0x00, 0x00, 0x00, 0x07, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x74, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e,
    0x00, 0x18, 0x00, 0x14, 0x00, 0x10, 0x00, 0x0c, 0x00, 0x08, 0x00, 0x07, 0x00,
    0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x10, 0x00, 0x00, 0x00, 0x18,
    0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x00, 0x00, 0x00, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00,
    0x00, 0xd2, 0x91, 0x43, 0x38, 0x01, 0x00, 0x00, 0x00, 0x40, 0xce, 0x42, 0x40,
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x58,
    0x43, 0x5f, 0x66, 0x63, 0x5f, 0x64, 0x65, 0x65, 0x70, 0x69, 0x6e, 0x5f, 0x61,
    0x6e, 0x79, 0x6f, 0x75, 0x74, 0x5f, 0x30, 0x2f, 0x6f, 0x75, 0x74, 0x70, 0x75,
    0x74, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x10, 0x00, 0x00, 0x00, 0xbc, 0xff, 0xff, 0xff, 0x10, 0x00, 0x00, 0x00, 0x06,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x28, 0x00, 0x00, 0x00, 0x1d, 0x00,
    0x00, 0x00, 0x58, 0x43, 0x5f, 0x66, 0x63, 0x5f, 0x64, 0x65, 0x65, 0x70, 0x69,
    0x6e, 0x5f, 0x61, 0x6e, 0x79, 0x6f, 0x75, 0x74, 0x5f, 0x30, 0x2f, 0x77, 0x65,
    0x69, 0x67, 0x68, 0x74, 0x73, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x10,
    0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x14, 0x00, 0x10, 0x00,
    0x0f, 0x00, 0x08, 0x00, 0x04, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,
    0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x30, 0x00, 0x00, 0x00,
    0x26, 0x00, 0x00, 0x00, 0x58, 0x43, 0x5f, 0x66, 0x63, 0x5f, 0x64, 0x65, 0x65,
    0x70, 0x69, 0x6e, 0x5f, 0x61, 0x6e, 0x79, 0x6f, 0x75, 0x74, 0x5f, 0x30, 0x2f,
    0x62, 0x69, 0x61, 0x73, 0x5f, 0x73, 0x68, 0x69, 0x66, 0x74, 0x5f, 0x73, 0x63,
    0x61, 0x6c, 0x65, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x07, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x7a, 0xfe, 0xff, 0xff, 0x14,
    0x00, 0x00, 0x00, 0x4c, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x09, 0x64, 0x00, 0x00, 0x00, 0x6c, 0xfe, 0xff, 0xff, 0x10, 0x00, 0x00,
    0x00, 0x1c, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00,
    0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xaa, 0x7b, 0xbe, 0x3b, 0x01, 0x00,
    0x00, 0x00, 0x2e, 0xbd, 0xbd, 0x3f, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x1e, 0x00, 0x00, 0x00, 0x58, 0x43, 0x5f, 0x72, 0x65, 0x71, 0x75, 0x61,
    0x6e, 0x74, 0x69, 0x7a, 0x65, 0x5f, 0x31, 0x36, 0x5f, 0x74, 0x6f, 0x5f, 0x38,
    0x5f, 0x31, 0x2f, 0x6f, 0x75, 0x74, 0x70, 0x75, 0x74, 0x00, 0x00, 0x02, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e,
    0x00, 0x14, 0x00, 0x10, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x08, 0x00, 0x04, 0x00,
    0x0e, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x44, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x09, 0x60, 0x00, 0x00, 0x00, 0xfc, 0xfe, 0xff, 0xff, 0x10, 0x00,
    0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00,
    0x00, 0x01, 0x00, 0x00, 0x00, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0x01, 0x00, 0x00, 0x00, 0xd2, 0x91, 0x43, 0x3c, 0x01, 0x00, 0x00, 0x00, 0x40,
    0xce, 0x42, 0x40, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00,
    0x00, 0x00, 0x58, 0x43, 0x5f, 0x72, 0x65, 0x71, 0x75, 0x61, 0x6e, 0x74, 0x69,
    0x7a, 0x65, 0x5f, 0x31, 0x36, 0x5f, 0x74, 0x6f, 0x5f, 0x38, 0x5f, 0x30, 0x2f,
    0x6f, 0x75, 0x74, 0x70, 0x75, 0x74, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x8a, 0xff, 0xff, 0xff, 0x14, 0x00,
    0x00, 0x00, 0x48, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x09, 0x54, 0x00, 0x00, 0x00, 0x7c, 0xff, 0xff, 0xff, 0x10, 0x00, 0x00, 0x00,
    0x18, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00,
    0x00, 0x00, 0x5d, 0x4f, 0xc9, 0x3c, 0x01, 0x00, 0x00, 0x00, 0x0e, 0x86, 0xc8,
    0x40, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00,
    0x64, 0x65, 0x6e, 0x73, 0x65, 0x5f, 0x32, 0x5f, 0x69, 0x6e, 0x70, 0x75, 0x74,
    0x5f, 0x69, 0x6e, 0x74, 0x38, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x18, 0x00, 0x14,
    0x00, 0x13, 0x00, 0x0c, 0x00, 0x08, 0x00, 0x04, 0x00, 0x0e, 0x00, 0x00, 0x00,
    0x20, 0x00, 0x00, 0x00, 0x54, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x09, 0x6c, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x14, 0x00, 0x10, 0x00,
    0x0c, 0x00, 0x08, 0x00, 0x04, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,
    0x00, 0x18, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x1a, 0xde, 0x0a, 0x3c, 0x01, 0x00, 0x00, 0x00, 0x66, 0x64,
    0x87, 0x3f, 0x01, 0x00, 0x00, 0x00, 0x13, 0x42, 0x8d, 0xbf, 0x1e, 0x00, 0x00,
    0x00, 0x58, 0x43, 0x5f, 0x72, 0x65, 0x71, 0x75, 0x61, 0x6e, 0x74, 0x69, 0x7a,
    0x65, 0x5f, 0x31, 0x36, 0x5f, 0x74, 0x6f, 0x5f, 0x38, 0x5f, 0x32, 0x2f, 0x6f,
    0x75, 0x74, 0x70, 0x75, 0x74, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00,
    0x00, 0x04, 0x00, 0x00, 0x00, 0xd8, 0xff, 0xff, 0xff, 0x08, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x20, 0x15, 0x00, 0x00, 0x00, 0x58, 0x43, 0x5f, 0x72, 0x65,
    0x71, 0x75, 0x61, 0x6e, 0x74, 0x69, 0x7a, 0x65, 0x5f, 0x31, 0x36, 0x5f, 0x74,
    0x6f, 0x5f, 0x38, 0x00, 0x00, 0x00, 0x08, 0x00, 0x0c, 0x00, 0x0b, 0x00, 0x04,
    0x00, 0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20,
    0x13, 0x00, 0x00, 0x00, 0x58, 0x43, 0x5f, 0x66, 0x63, 0x5f, 0x64, 0x65, 0x65,
    0x70, 0x69, 0x6e, 0x5f, 0x61, 0x6e, 0x79, 0x6f, 0x75, 0x74, 0x00,
};
const int g_model_len = 3560;
