/* Copyright (c) 2017 Evan Nemerson <evan@nemerson.com>
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "../x86-internal.h"
#include "../../../simde/x86/ssse3.h"

#include <stdio.h>

static MunitResult
test_simde_mm_alignr_epi8(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  const struct {
    simde__m128i a;
    simde__m128i b;
    simde__m128i r;
  } test_vec[8] = {
    { simde_mm_set_epi8(0x0e, 0xa6, 0x78, 0xc5, 0x44, 0x8c, 0x1c, 0xc6,
			0xd6, 0x3a, 0x0a, 0xa5, 0x36, 0xb7, 0xb8, 0x8a),
      simde_mm_set_epi8(0x1c, 0x44, 0xfe, 0xcd, 0x20, 0x7b, 0x4a, 0xaf,
			0x2a, 0x99, 0xf9, 0x5b, 0xcb, 0xda, 0xf8, 0x99),
      simde_mm_set_epi8(0x00, 0x0e, 0xa6, 0x78, 0xc5, 0x44, 0x8c, 0x1c,
			0xc6, 0xd6, 0x3a, 0x0a, 0xa5, 0x36, 0xb7, 0xb8) },
    { simde_mm_set_epi8(0x39, 0x47, 0x02, 0x20, 0xd3, 0x40, 0x93, 0x07,
			0xff, 0xd4, 0xed, 0x44, 0xc5, 0xc9, 0x57, 0x8b),
      simde_mm_set_epi8(0xfa, 0x88, 0xf3, 0xa9, 0xbb, 0xde, 0x94, 0x6f,
			0x6c, 0x1b, 0xea, 0xc3, 0x33, 0x72, 0x48, 0x3a),
      simde_mm_set_epi8(0x00, 0x39, 0x47, 0x02, 0x20, 0xd3, 0x40, 0x93,
			0x07, 0xff, 0xd4, 0xed, 0x44, 0xc5, 0xc9, 0x57) },
    { simde_mm_set_epi8(0x77, 0x95, 0xd2, 0x06, 0xce, 0x70, 0xc2, 0x4e,
			0x9e, 0x4f, 0x53, 0xc4, 0xc7, 0xaf, 0x6b, 0x44),
      simde_mm_set_epi8(0x65, 0xea, 0x07, 0xb7, 0x82, 0xf1, 0xad, 0x6b,
			0x47, 0xd9, 0x5f, 0x75, 0xcb, 0x02, 0x70, 0x2d),
      simde_mm_set_epi8(0x00, 0x77, 0x95, 0xd2, 0x06, 0xce, 0x70, 0xc2,
			0x4e, 0x9e, 0x4f, 0x53, 0xc4, 0xc7, 0xaf, 0x6b) },
    { simde_mm_set_epi8(0x27, 0x27, 0x35, 0x16, 0x41, 0xeb, 0xb5, 0xd6,
			0x7d, 0x83, 0xc7, 0x1f, 0xb9, 0x74, 0xad, 0x9d),
      simde_mm_set_epi8(0x8f, 0x7c, 0xef, 0x14, 0xe6, 0xe6, 0xa4, 0x40,
			0xc6, 0xd2, 0xb7, 0xe4, 0x93, 0x67, 0xc1, 0x44),
      simde_mm_set_epi8(0x00, 0x27, 0x27, 0x35, 0x16, 0x41, 0xeb, 0xb5,
			0xd6, 0x7d, 0x83, 0xc7, 0x1f, 0xb9, 0x74, 0xad) },
    { simde_mm_set_epi8(0x6c, 0xb7, 0x16, 0xc7, 0x11, 0x7d, 0x8b, 0x68,
			0x20, 0x1c, 0x0b, 0x41, 0x93, 0xe4, 0x25, 0x3b),
      simde_mm_set_epi8(0xde, 0xdf, 0xa5, 0xa0, 0xac, 0xda, 0x89, 0x41,
			0x1a, 0x28, 0xc7, 0xc7, 0x16, 0x36, 0x9a, 0xbe),
      simde_mm_set_epi8(0x00, 0x6c, 0xb7, 0x16, 0xc7, 0x11, 0x7d, 0x8b,
			0x68, 0x20, 0x1c, 0x0b, 0x41, 0x93, 0xe4, 0x25) },
    { simde_mm_set_epi8(0xdb, 0xac, 0xcc, 0x45, 0xab, 0x27, 0x91, 0x2f,
			0xe5, 0xed, 0x3c, 0x06, 0xe3, 0x9d, 0x2a, 0x89),
      simde_mm_set_epi8(0xd0, 0x98, 0x42, 0x74, 0xd9, 0xb8, 0x8a, 0xcc,
			0x55, 0x28, 0x89, 0xfa, 0xd3, 0x16, 0x6f, 0x9a),
      simde_mm_set_epi8(0x00, 0xdb, 0xac, 0xcc, 0x45, 0xab, 0x27, 0x91,
			0x2f, 0xe5, 0xed, 0x3c, 0x06, 0xe3, 0x9d, 0x2a) },
    { simde_mm_set_epi8(0x72, 0xae, 0x35, 0x1f, 0xa3, 0x0d, 0xc0, 0x4c,
			0x85, 0x0c, 0x09, 0x79, 0x46, 0x8c, 0xa5, 0x69),
      simde_mm_set_epi8(0x13, 0xa0, 0x97, 0xc2, 0x9b, 0x6c, 0x15, 0xb7,
			0xe4, 0x4c, 0x45, 0x88, 0xb8, 0x2f, 0xa8, 0x6d),
      simde_mm_set_epi8(0x00, 0x72, 0xae, 0x35, 0x1f, 0xa3, 0x0d, 0xc0,
			0x4c, 0x85, 0x0c, 0x09, 0x79, 0x46, 0x8c, 0xa5) },
    { simde_mm_set_epi8(0xb8, 0xa4, 0xd1, 0x25, 0xbc, 0x6e, 0xb4, 0x07,
			0x5c, 0x3c, 0x82, 0x4e, 0x4e, 0x8f, 0x89, 0x88),
      simde_mm_set_epi8(0xcd, 0xdc, 0xa8, 0x18, 0x32, 0xef, 0xe7, 0x84,
			0x82, 0xdc, 0x0b, 0x30, 0x15, 0x12, 0x4f, 0xc9),
      simde_mm_set_epi8(0x00, 0xb8, 0xa4, 0xd1, 0x25, 0xbc, 0x6e, 0xb4,
			0x07, 0x5c, 0x3c, 0x82, 0x4e, 0x4e, 0x8f, 0x89) }
  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])); i++) {
    simde__m128i r = simde_mm_alignr_epi8(test_vec[i].a, test_vec[i].b, 17);
    simde_assert_m128_i8(r, ==, test_vec[i].r);
  }

  return MUNIT_OK;
}

static MunitResult
test_simde_mm_shuffle_epi8(const MunitParameter params[], void* data) {
  (void) params;
  (void) data;

  const struct {
    simde__m128i a;
    simde__m128i b;
    simde__m128i r;
  } test_vec[8] = {
    { simde_mm_set_epi8(0x68, 0xb8, 0x67, 0x53, 0x63, 0xcb, 0xf5, 0x64,
			0xb1, 0xa8, 0xbb, 0xde, 0x62, 0xf0, 0x9b, 0x43),
      simde_mm_set_epi8(0x8f, 0xc0, 0x0c, 0xa5, 0xfe, 0xa1, 0xb7, 0xe0,
			0xd9, 0xe7, 0x73, 0x71, 0x32, 0xf8, 0x20, 0x24),
      simde_mm_set_epi8(0x00, 0x00, 0x53, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x62, 0x9b, 0xf0, 0x00, 0x43, 0xde) },
    { simde_mm_set_epi8(0x65, 0xfa, 0xbd, 0xd7, 0xb4, 0xfc, 0x05, 0x2c,
			0xb4, 0x2d, 0xe5, 0x10, 0x21, 0x07, 0x5b, 0x88),
      simde_mm_set_epi8(0xf2, 0x24, 0x77, 0xe7, 0xb5, 0xae, 0x7e, 0x99,
			0x35, 0xf8, 0x5e, 0xdb, 0x4f, 0xbe, 0x21, 0x59),
      simde_mm_set_epi8(0x00, 0x10, 0xb4, 0x00, 0x00, 0x00, 0xfa, 0x00,
			0xe5, 0x00, 0xfa, 0x00, 0x65, 0x00, 0x5b, 0x05) },
    { simde_mm_set_epi8(0xba, 0xf3, 0x94, 0xab, 0xf8, 0x74, 0x1b, 0x34,
			0x34, 0x70, 0x14, 0xf4, 0xfa, 0x53, 0x4f, 0x22),
      simde_mm_set_epi8(0x5b, 0x8e, 0xef, 0xef, 0xb6, 0x34, 0x42, 0x57,
			0x9e, 0xcb, 0xfe, 0x0d, 0xe2, 0xa2, 0x24, 0x05),
      simde_mm_set_epi8(0xf8, 0x00, 0x00, 0x00, 0x00, 0xf4, 0x53, 0x34,
			0x00, 0x00, 0x00, 0x94, 0x00, 0x00, 0xf4, 0x14) },
    { simde_mm_set_epi8(0x9f, 0x7f, 0x0d, 0x92, 0x43, 0x29, 0x0f, 0x1d,
			0xbe, 0xd8, 0x12, 0xec, 0x8d, 0xfc, 0xd0, 0xc4),
      simde_mm_set_epi8(0xc6, 0x53, 0x66, 0xe2, 0xd5, 0x10, 0xd0, 0x20,
			0x5d, 0x7e, 0x2e, 0x15, 0xee, 0x4e, 0x2b, 0x28),
      simde_mm_set_epi8(0x00, 0x8d, 0xd8, 0x00, 0x00, 0xc4, 0x00, 0xc4,
			0x0d, 0x7f, 0x7f, 0x12, 0x00, 0x7f, 0x43, 0x1d) },
    { simde_mm_set_epi8(0xe4, 0x3f, 0x74, 0xed, 0x72, 0xa4, 0x19, 0x62,
			0x04, 0x0c, 0x51, 0xb3, 0x65, 0xf3, 0x86, 0xeb),
      simde_mm_set_epi8(0xd8, 0x14, 0x9b, 0xa8, 0x2c, 0x19, 0xd8, 0xf0,
			0xb1, 0x68, 0x19, 0x6a, 0xd3, 0x32, 0x89, 0x9f),
      simde_mm_set_epi8(0x00, 0xb3, 0x00, 0x00, 0xed, 0x19, 0x00, 0x00,
			0x00, 0x62, 0x19, 0xa4, 0x00, 0xf3, 0x00, 0x00) },
    { simde_mm_set_epi8(0xde, 0x84, 0x0d, 0x39, 0x30, 0x1a, 0x97, 0x4c,
			0x26, 0xb5, 0x43, 0x0f, 0x56, 0x34, 0xbd, 0x6f),
      simde_mm_set_epi8(0x7f, 0xee, 0x93, 0xdc, 0x3d, 0xa6, 0xeb, 0x54,
			0x43, 0x50, 0x21, 0x80, 0xa4, 0xaf, 0xd9, 0x74),
      simde_mm_set_epi8(0xde, 0x00, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x0f,
			0x56, 0x6f, 0xbd, 0x00, 0x00, 0x00, 0x00, 0x0f) },
    { simde_mm_set_epi8(0x0d, 0x52, 0x91, 0x0b, 0x52, 0xfb, 0xd6, 0xa4,
			0x55, 0x0b, 0x88, 0x79, 0x1c, 0xaa, 0xc6, 0x87),
      simde_mm_set_epi8(0x54, 0x3f, 0x7e, 0xf4, 0x3c, 0xed, 0x41, 0xec,
			0xd6, 0xca, 0xe4, 0x65, 0xcc, 0xad, 0xff, 0x0c),
      simde_mm_set_epi8(0x79, 0x0d, 0x52, 0x00, 0x0b, 0x00, 0xc6, 0x00,
			0x00, 0x00, 0x00, 0x88, 0x00, 0x00, 0x00, 0x0b) },
    { simde_mm_set_epi8(0x76, 0x1b, 0x22, 0xf5, 0x78, 0xff, 0xbe, 0xe2,
			0xc7, 0x50, 0xeb, 0x31, 0x80, 0x79, 0x01, 0xe0),
      simde_mm_set_epi8(0x69, 0xf7, 0x27, 0x4f, 0xcb, 0xf5, 0x91, 0x71,
			0xec, 0xad, 0x11, 0x6b, 0x22, 0x39, 0x05, 0x0b),
      simde_mm_set_epi8(0xbe, 0x00, 0xc7, 0x76, 0x00, 0x00, 0x00, 0x01,
			0x00, 0x00, 0x01, 0x78, 0x79, 0xbe, 0xeb, 0x78) }
  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])); i++) {
    simde__m128i r = simde_mm_shuffle_epi8(test_vec[i].a, test_vec[i].b);
    simde_assert_m128_i8(r, ==, test_vec[i].r);
  }

  return MUNIT_OK;
}

static MunitTest test_suite_tests[] = {
  { (char*) "/mm_alignr_epi8",      test_simde_mm_alignr_epi8,      NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { (char*) "/mm_shuffle_epi8",     test_simde_mm_shuffle_epi8,     NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },

  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

MunitSuite simde_ssse3_test_suite = {
  (char*) "/ssse3",
  test_suite_tests,
  NULL,
  1,
  MUNIT_SUITE_OPTION_NONE
};
