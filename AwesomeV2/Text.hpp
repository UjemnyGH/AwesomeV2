#pragma once
#include "Core.hpp"

namespace aws
{
#ifdef _WIN32
	const char* characters_atlas = "data/textures/characters.png";
#else
	const char* characters_atlas = "AwesomeV2/data/textures/characters.png";
#endif // _WIN32

	const float char_mul = 32.0f;
	const float char_column[16] = {0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f};
	const int offset[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };

	std::map<int, Vector> characters_map = {
		{0	*	offset[0], {0.0f	* char_mul,		char_column[0] * char_mul}},
		{1	*	offset[0], {1.0f	* char_mul,		char_column[0] * char_mul}},
		{2	*	offset[0], {2.0f	* char_mul,		char_column[0] * char_mul}},
		{3	*	offset[0], {3.0f	* char_mul,		char_column[0] * char_mul}},
		{4	*	offset[0], {4.0f	* char_mul,		char_column[0] * char_mul}},
		{5	*	offset[0], {5.0f	* char_mul,		char_column[0] * char_mul}},
		{6	*	offset[0], {6.0f	* char_mul,		char_column[0] * char_mul}},
		{7	*	offset[0], {7.0f	* char_mul,		char_column[0] * char_mul}},
		{8	*	offset[0], {8.0f	* char_mul,		char_column[0] * char_mul}},
		{9	*	offset[0], {9.0f	* char_mul,		char_column[0] * char_mul}},
		{10	*	offset[0], {10.0f	* char_mul,		char_column[0] * char_mul}},
		{11	*	offset[0], {11.0f	* char_mul,		char_column[0] * char_mul}},
		{12	*	offset[0], {12.0f	* char_mul,		char_column[0] * char_mul}},
		{13	*	offset[0], {13.0f	* char_mul,		char_column[0] * char_mul}},
		{14	*	offset[0], {14.0f	* char_mul,		char_column[0] * char_mul}},
		{15	*	offset[0], {15.0f	* char_mul,		char_column[0] * char_mul}},
		{16	*	offset[0], {16.0f	* char_mul,		char_column[0] * char_mul}},

		{0	*	offset[1], {0.0f	* char_mul,		char_column[1] * char_mul}},
		{1	*	offset[1], {1.0f	* char_mul,		char_column[1] * char_mul}},
		{2	*	offset[1], {2.0f	* char_mul,		char_column[1] * char_mul}},
		{3	*	offset[1], {3.0f	* char_mul,		char_column[1] * char_mul}},
		{4	*	offset[1], {4.0f	* char_mul,		char_column[1] * char_mul}},
		{5	*	offset[1], {5.0f	* char_mul,		char_column[1] * char_mul}},
		{6	*	offset[1], {6.0f	* char_mul,		char_column[1] * char_mul}},
		{7	*	offset[1], {7.0f	* char_mul,		char_column[1] * char_mul}},
		{8	*	offset[1], {8.0f	* char_mul,		char_column[1] * char_mul}},
		{9	*	offset[1], {9.0f	* char_mul,		char_column[1] * char_mul}},
		{10	*	offset[1], {10.0f	* char_mul,		char_column[1] * char_mul}},
		{11	*	offset[1], {11.0f	* char_mul,		char_column[1] * char_mul}},
		{12	*	offset[1], {12.0f	* char_mul,		char_column[1] * char_mul}},
		{13	*	offset[1], {13.0f	* char_mul,		char_column[1] * char_mul}},
		{14	*	offset[1], {14.0f	* char_mul,		char_column[1] * char_mul}},
		{15	*	offset[1], {15.0f	* char_mul,		char_column[1] * char_mul}},
		{16	*	offset[1], {16.0f	* char_mul,		char_column[1] * char_mul}},

		{0	*	offset[2], {0.0f	* char_mul,		char_column[2] * char_mul}},
		{1	*	offset[2], {1.0f	* char_mul,		char_column[2] * char_mul}},
		{2	*	offset[2], {2.0f	* char_mul,		char_column[2] * char_mul}},
		{3	*	offset[2], {3.0f	* char_mul,		char_column[2] * char_mul}},
		{4	*	offset[2], {4.0f	* char_mul,		char_column[2] * char_mul}},
		{5	*	offset[2], {5.0f	* char_mul,		char_column[2] * char_mul}},
		{6	*	offset[2], {6.0f	* char_mul,		char_column[2] * char_mul}},
		{7	*	offset[2], {7.0f	* char_mul,		char_column[2] * char_mul}},
		{8	*	offset[2], {8.0f	* char_mul,		char_column[2] * char_mul}},
		{9	*	offset[2], {9.0f	* char_mul,		char_column[2] * char_mul}},
		{10	*	offset[2], {10.0f	* char_mul,		char_column[2] * char_mul}},
		{11	*	offset[2], {11.0f	* char_mul,		char_column[2] * char_mul}},
		{12	*	offset[2], {12.0f	* char_mul,		char_column[2] * char_mul}},
		{13	*	offset[2], {13.0f	* char_mul,		char_column[2] * char_mul}},
		{14	*	offset[2], {14.0f	* char_mul,		char_column[2] * char_mul}},
		{15	*	offset[2], {15.0f	* char_mul,		char_column[2] * char_mul}},
		{16	*	offset[2], {16.0f	* char_mul,		char_column[2] * char_mul}},

		{0	*	offset[3], {0.0f	* char_mul,		char_column[3] * char_mul}},
		{1	*	offset[3], {1.0f	* char_mul,		char_column[3] * char_mul}},
		{2	*	offset[3], {2.0f	* char_mul,		char_column[3] * char_mul}},
		{3	*	offset[3], {3.0f	* char_mul,		char_column[3] * char_mul}},
		{4	*	offset[3], {4.0f	* char_mul,		char_column[3] * char_mul}},
		{5	*	offset[3], {5.0f	* char_mul,		char_column[3] * char_mul}},
		{6	*	offset[3], {6.0f	* char_mul,		char_column[3] * char_mul}},
		{7	*	offset[3], {7.0f	* char_mul,		char_column[3] * char_mul}},
		{8	*	offset[3], {8.0f	* char_mul,		char_column[3] * char_mul}},
		{9	*	offset[3], {9.0f	* char_mul,		char_column[3] * char_mul}},
		{10	*	offset[3], {10.0f	* char_mul,		char_column[3] * char_mul}},
		{11	*	offset[3], {11.0f	* char_mul,		char_column[3] * char_mul}},
		{12	*	offset[3], {12.0f	* char_mul,		char_column[3] * char_mul}},
		{13	*	offset[3], {13.0f	* char_mul,		char_column[3] * char_mul}},
		{14	*	offset[3], {14.0f	* char_mul,		char_column[3] * char_mul}},
		{15	*	offset[3], {15.0f	* char_mul,		char_column[3] * char_mul}},
		{16	*	offset[3], {16.0f	* char_mul,		char_column[3] * char_mul}},

		{0	*	offset[4], {0.0f	* char_mul,		char_column[4] * char_mul}},
		{1	*	offset[4], {1.0f	* char_mul,		char_column[4] * char_mul}},
		{2	*	offset[4], {2.0f	* char_mul,		char_column[4] * char_mul}},
		{3	*	offset[4], {3.0f	* char_mul,		char_column[4] * char_mul}},
		{4	*	offset[4], {4.0f	* char_mul,		char_column[4] * char_mul}},
		{5	*	offset[4], {5.0f	* char_mul,		char_column[4] * char_mul}},
		{6	*	offset[4], {6.0f	* char_mul,		char_column[4] * char_mul}},
		{7	*	offset[4], {7.0f	* char_mul,		char_column[4] * char_mul}},
		{8	*	offset[4], {8.0f	* char_mul,		char_column[4] * char_mul}},
		{9	*	offset[4], {9.0f	* char_mul,		char_column[4] * char_mul}},
		{10	*	offset[4], {10.0f	* char_mul,		char_column[4] * char_mul}},
		{11	*	offset[4], {11.0f	* char_mul,		char_column[4] * char_mul}},
		{12	*	offset[4], {12.0f	* char_mul,		char_column[4] * char_mul}},
		{13	*	offset[4], {13.0f	* char_mul,		char_column[4] * char_mul}},
		{14	*	offset[4], {14.0f	* char_mul,		char_column[4] * char_mul}},
		{15	*	offset[4], {15.0f	* char_mul,		char_column[4] * char_mul}},
		{16	*	offset[4], {16.0f	* char_mul,		char_column[4] * char_mul}},

		{0	*	offset[5], {0.0f	* char_mul,		char_column[5] * char_mul}},
		{1	*	offset[5], {1.0f	* char_mul,		char_column[5] * char_mul}},
		{2	*	offset[5], {2.0f	* char_mul,		char_column[5] * char_mul}},
		{3	*	offset[5], {3.0f	* char_mul,		char_column[5] * char_mul}},
		{4	*	offset[5], {4.0f	* char_mul,		char_column[5] * char_mul}},
		{5	*	offset[5], {5.0f	* char_mul,		char_column[5] * char_mul}},
		{6	*	offset[5], {6.0f	* char_mul,		char_column[5] * char_mul}},
		{7	*	offset[5], {7.0f	* char_mul,		char_column[5] * char_mul}},
		{8	*	offset[5], {8.0f	* char_mul,		char_column[5] * char_mul}},
		{9	*	offset[5], {9.0f	* char_mul,		char_column[5] * char_mul}},
		{10	*	offset[5], {10.0f	* char_mul,		char_column[5] * char_mul}},
		{11	*	offset[5], {11.0f	* char_mul,		char_column[5] * char_mul}},
		{12	*	offset[5], {12.0f	* char_mul,		char_column[5] * char_mul}},
		{13	*	offset[5], {13.0f	* char_mul,		char_column[5] * char_mul}},
		{14	*	offset[5], {14.0f	* char_mul,		char_column[5] * char_mul}},
		{15	*	offset[5], {15.0f	* char_mul,		char_column[5] * char_mul}},
		{16	*	offset[5], {16.0f	* char_mul,		char_column[5] * char_mul}},

		{0	*	offset[6], {0.0f	* char_mul,		char_column[6] * char_mul}},
		{1	*	offset[6], {1.0f	* char_mul,		char_column[6] * char_mul}},
		{2	*	offset[6], {2.0f	* char_mul,		char_column[6] * char_mul}},
		{3	*	offset[6], {3.0f	* char_mul,		char_column[6] * char_mul}},
		{4	*	offset[6], {4.0f	* char_mul,		char_column[6] * char_mul}},
		{5	*	offset[6], {5.0f	* char_mul,		char_column[6] * char_mul}},
		{6	*	offset[6], {6.0f	* char_mul,		char_column[6] * char_mul}},
		{7	*	offset[6], {7.0f	* char_mul,		char_column[6] * char_mul}},
		{8	*	offset[6], {8.0f	* char_mul,		char_column[6] * char_mul}},
		{9	*	offset[6], {9.0f	* char_mul,		char_column[6] * char_mul}},
		{10	*	offset[6], {10.0f	* char_mul,		char_column[6] * char_mul}},
		{11	*	offset[6], {11.0f	* char_mul,		char_column[6] * char_mul}},
		{12	*	offset[6], {12.0f	* char_mul,		char_column[6] * char_mul}},
		{13	*	offset[6], {13.0f	* char_mul,		char_column[6] * char_mul}},
		{14	*	offset[6], {14.0f	* char_mul,		char_column[6] * char_mul}},
		{15	*	offset[6], {15.0f	* char_mul,		char_column[6] * char_mul}},
		{16	*	offset[6], {16.0f	* char_mul,		char_column[6] * char_mul}},

		{0	*	offset[7], {0.0f	* char_mul,		char_column[7] * char_mul}},
		{1	*	offset[7], {1.0f	* char_mul,		char_column[7] * char_mul}},
		{2	*	offset[7], {2.0f	* char_mul,		char_column[7] * char_mul}},
		{3	*	offset[7], {3.0f	* char_mul,		char_column[7] * char_mul}},
		{4	*	offset[7], {4.0f	* char_mul,		char_column[7] * char_mul}},
		{5	*	offset[7], {5.0f	* char_mul,		char_column[7] * char_mul}},
		{6	*	offset[7], {6.0f	* char_mul,		char_column[7] * char_mul}},
		{7	*	offset[7], {7.0f	* char_mul,		char_column[7] * char_mul}},
		{8	*	offset[7], {8.0f	* char_mul,		char_column[7] * char_mul}},
		{9	*	offset[7], {9.0f	* char_mul,		char_column[7] * char_mul}},
		{10	*	offset[7], {10.0f	* char_mul,		char_column[7] * char_mul}},
		{11	*	offset[7], {11.0f	* char_mul,		char_column[7] * char_mul}},
		{12	*	offset[7], {12.0f	* char_mul,		char_column[7] * char_mul}},
		{13	*	offset[7], {13.0f	* char_mul,		char_column[7] * char_mul}},
		{14	*	offset[7], {14.0f	* char_mul,		char_column[7] * char_mul}},
		{15	*	offset[7], {15.0f	* char_mul,		char_column[7] * char_mul}},
		{16	*	offset[7], {16.0f	* char_mul,		char_column[7] * char_mul}},

		{0	*	offset[8], {0.0f	* char_mul,		char_column[8] * char_mul}},
		{1	*	offset[8], {1.0f	* char_mul,		char_column[8] * char_mul}},
		{2	*	offset[8], {2.0f	* char_mul,		char_column[8] * char_mul}},
		{3	*	offset[8], {3.0f	* char_mul,		char_column[8] * char_mul}},
		{4	*	offset[8], {4.0f	* char_mul,		char_column[8] * char_mul}},
		{5	*	offset[8], {5.0f	* char_mul,		char_column[8] * char_mul}},
		{6	*	offset[8], {6.0f	* char_mul,		char_column[8] * char_mul}},
		{7	*	offset[8], {7.0f	* char_mul,		char_column[8] * char_mul}},
		{8	*	offset[8], {8.0f	* char_mul,		char_column[8] * char_mul}},
		{9	*	offset[8], {9.0f	* char_mul,		char_column[8] * char_mul}},
		{10	*	offset[8], {10.0f	* char_mul,		char_column[8] * char_mul}},
		{11	*	offset[8], {11.0f	* char_mul,		char_column[8] * char_mul}},
		{12	*	offset[8], {12.0f	* char_mul,		char_column[8] * char_mul}},
		{13	*	offset[8], {13.0f	* char_mul,		char_column[8] * char_mul}},
		{14	*	offset[8], {14.0f	* char_mul,		char_column[8] * char_mul}},
		{15	*	offset[8], {15.0f	* char_mul,		char_column[8] * char_mul}},
		{16	*	offset[8], {16.0f	* char_mul,		char_column[8] * char_mul}},

		{0	*	offset[9], {0.0f	* char_mul,		char_column[9] * char_mul}},
		{1	*	offset[9], {1.0f	* char_mul,		char_column[9] * char_mul}},
		{2	*	offset[9], {2.0f	* char_mul,		char_column[9] * char_mul}},
		{3	*	offset[9], {3.0f	* char_mul,		char_column[9] * char_mul}},
		{4	*	offset[9], {4.0f	* char_mul,		char_column[9] * char_mul}},
		{5	*	offset[9], {5.0f	* char_mul,		char_column[9] * char_mul}},
		{6	*	offset[9], {6.0f	* char_mul,		char_column[9] * char_mul}},
		{7	*	offset[9], {7.0f	* char_mul,		char_column[9] * char_mul}},
		{8	*	offset[9], {8.0f	* char_mul,		char_column[9] * char_mul}},
		{9	*	offset[9], {9.0f	* char_mul,		char_column[9] * char_mul}},
		{10	*	offset[9], {10.0f	* char_mul,		char_column[9] * char_mul}},
		{11	*	offset[9], {11.0f	* char_mul,		char_column[9] * char_mul}},
		{12	*	offset[9], {12.0f	* char_mul,		char_column[9] * char_mul}},
		{13	*	offset[9], {13.0f	* char_mul,		char_column[9] * char_mul}},
		{14	*	offset[9], {14.0f	* char_mul,		char_column[9] * char_mul}},
		{15	*	offset[9], {15.0f	* char_mul,		char_column[9] * char_mul}},
		{16	*	offset[9], {16.0f	* char_mul,		char_column[9] * char_mul}},

		{0	*	offset[10], {0.0f	* char_mul,		char_column[10] * char_mul}},
		{1	*	offset[10], {1.0f	* char_mul,		char_column[10] * char_mul}},
		{2	*	offset[10], {2.0f	* char_mul,		char_column[10] * char_mul}},
		{3	*	offset[10], {3.0f	* char_mul,		char_column[10] * char_mul}},
		{4	*	offset[10], {4.0f	* char_mul,		char_column[10] * char_mul}},
		{5	*	offset[10], {5.0f	* char_mul,		char_column[10] * char_mul}},
		{6	*	offset[10], {6.0f	* char_mul,		char_column[10] * char_mul}},
		{7	*	offset[10], {7.0f	* char_mul,		char_column[10] * char_mul}},
		{8	*	offset[10], {8.0f	* char_mul,		char_column[10] * char_mul}},
		{9	*	offset[10], {9.0f	* char_mul,		char_column[10] * char_mul}},
		{10	*	offset[10], {10.0f	* char_mul,		char_column[10] * char_mul}},
		{11	*	offset[10], {11.0f	* char_mul,		char_column[10] * char_mul}},
		{12	*	offset[10], {12.0f	* char_mul,		char_column[10] * char_mul}},
		{13	*	offset[10], {13.0f	* char_mul,		char_column[10] * char_mul}},
		{14	*	offset[10], {14.0f	* char_mul,		char_column[10] * char_mul}},
		{15	*	offset[10], {15.0f	* char_mul,		char_column[10] * char_mul}},
		{16	*	offset[10], {16.0f	* char_mul,		char_column[10] * char_mul}},

		{0	*	offset[11], {0.0f	* char_mul,		char_column[11] * char_mul}},
		{1	*	offset[11], {1.0f	* char_mul,		char_column[11] * char_mul}},
		{2	*	offset[11], {2.0f	* char_mul,		char_column[11] * char_mul}},
		{3	*	offset[11], {3.0f	* char_mul,		char_column[11] * char_mul}},
		{4	*	offset[11], {4.0f	* char_mul,		char_column[11] * char_mul}},
		{5	*	offset[11], {5.0f	* char_mul,		char_column[11] * char_mul}},
		{6	*	offset[11], {6.0f	* char_mul,		char_column[11] * char_mul}},
		{7	*	offset[11], {7.0f	* char_mul,		char_column[11] * char_mul}},
		{8	*	offset[11], {8.0f	* char_mul,		char_column[11] * char_mul}},
		{9	*	offset[11], {9.0f	* char_mul,		char_column[11] * char_mul}},
		{10	*	offset[11], {10.0f	* char_mul,		char_column[11] * char_mul}},
		{11	*	offset[11], {11.0f	* char_mul,		char_column[11] * char_mul}},
		{12	*	offset[11], {12.0f	* char_mul,		char_column[11] * char_mul}},
		{13	*	offset[11], {13.0f	* char_mul,		char_column[11] * char_mul}},
		{14	*	offset[11], {14.0f	* char_mul,		char_column[11] * char_mul}},
		{15	*	offset[11], {15.0f	* char_mul,		char_column[11] * char_mul}},
		{16	*	offset[11], {16.0f	* char_mul,		char_column[11] * char_mul}},

		{0	*	offset[12], {0.0f	* char_mul,		char_column[12] * char_mul}},
		{1	*	offset[12], {1.0f	* char_mul,		char_column[12] * char_mul}},
		{2	*	offset[12], {2.0f	* char_mul,		char_column[12] * char_mul}},
		{3	*	offset[12], {3.0f	* char_mul,		char_column[12] * char_mul}},
		{4	*	offset[12], {4.0f	* char_mul,		char_column[12] * char_mul}},
		{5	*	offset[12], {5.0f	* char_mul,		char_column[12] * char_mul}},
		{6	*	offset[12], {6.0f	* char_mul,		char_column[12] * char_mul}},
		{7	*	offset[12], {7.0f	* char_mul,		char_column[12] * char_mul}},
		{8	*	offset[12], {8.0f	* char_mul,		char_column[12] * char_mul}},
		{9	*	offset[12], {9.0f	* char_mul,		char_column[12] * char_mul}},
		{10	*	offset[12], {10.0f	* char_mul,		char_column[12] * char_mul}},
		{11	*	offset[12], {11.0f	* char_mul,		char_column[12] * char_mul}},
		{12	*	offset[12], {12.0f	* char_mul,		char_column[12] * char_mul}},
		{13	*	offset[12], {13.0f	* char_mul,		char_column[12] * char_mul}},
		{14	*	offset[12], {14.0f	* char_mul,		char_column[12] * char_mul}},
		{15	*	offset[12], {15.0f	* char_mul,		char_column[12] * char_mul}},
		{16	*	offset[12], {16.0f	* char_mul,		char_column[12] * char_mul}},

		{0	*	offset[13], {0.0f	* char_mul,		char_column[13] * char_mul}},
		{1	*	offset[13], {1.0f	* char_mul,		char_column[13] * char_mul}},
		{2	*	offset[13], {2.0f	* char_mul,		char_column[13] * char_mul}},
		{3	*	offset[13], {3.0f	* char_mul,		char_column[13] * char_mul}},
		{4	*	offset[13], {4.0f	* char_mul,		char_column[13] * char_mul}},
		{5	*	offset[13], {5.0f	* char_mul,		char_column[13] * char_mul}},
		{6	*	offset[13], {6.0f	* char_mul,		char_column[13] * char_mul}},
		{7	*	offset[13], {7.0f	* char_mul,		char_column[13] * char_mul}},
		{8	*	offset[13], {8.0f	* char_mul,		char_column[13] * char_mul}},
		{9	*	offset[13], {9.0f	* char_mul,		char_column[13] * char_mul}},
		{10	*	offset[13], {10.0f	* char_mul,		char_column[13] * char_mul}},
		{11	*	offset[13], {11.0f	* char_mul,		char_column[13] * char_mul}},
		{12	*	offset[13], {12.0f	* char_mul,		char_column[13] * char_mul}},
		{13	*	offset[13], {13.0f	* char_mul,		char_column[13] * char_mul}},
		{14	*	offset[13], {14.0f	* char_mul,		char_column[13] * char_mul}},
		{15	*	offset[13], {15.0f	* char_mul,		char_column[13] * char_mul}},
		{16	*	offset[13], {16.0f	* char_mul,		char_column[13] * char_mul}},

		{0	*	offset[14], {0.0f	* char_mul,		char_column[14] * char_mul}},
		{1	*	offset[14], {1.0f	* char_mul,		char_column[14] * char_mul}},
		{2	*	offset[14], {2.0f	* char_mul,		char_column[14] * char_mul}},
		{3	*	offset[14], {3.0f	* char_mul,		char_column[14] * char_mul}},
		{4	*	offset[14], {4.0f	* char_mul,		char_column[14] * char_mul}},
		{5	*	offset[14], {5.0f	* char_mul,		char_column[14] * char_mul}},
		{6	*	offset[14], {6.0f	* char_mul,		char_column[14] * char_mul}},
		{7	*	offset[14], {7.0f	* char_mul,		char_column[14] * char_mul}},
		{8	*	offset[14], {8.0f	* char_mul,		char_column[14] * char_mul}},
		{9	*	offset[14], {9.0f	* char_mul,		char_column[14] * char_mul}},
		{10	*	offset[14], {10.0f	* char_mul,		char_column[14] * char_mul}},
		{11	*	offset[14], {11.0f	* char_mul,		char_column[14] * char_mul}},
		{12	*	offset[14], {12.0f	* char_mul,		char_column[14] * char_mul}},
		{13	*	offset[14], {13.0f	* char_mul,		char_column[14] * char_mul}},
		{14	*	offset[14], {14.0f	* char_mul,		char_column[14] * char_mul}},
		{15	*	offset[14], {15.0f	* char_mul,		char_column[14] * char_mul}},
		{16	*	offset[14], {16.0f	* char_mul,		char_column[14] * char_mul}},

		{0	*	offset[15], {0.0f	* char_mul,		char_column[15] * char_mul}},
		{1	*	offset[15], {1.0f	* char_mul,		char_column[15] * char_mul}},
		{2	*	offset[15], {2.0f	* char_mul,		char_column[15] * char_mul}},
		{3	*	offset[15], {3.0f	* char_mul,		char_column[15] * char_mul}},
		{4	*	offset[15], {4.0f	* char_mul,		char_column[15] * char_mul}},
		{5	*	offset[15], {5.0f	* char_mul,		char_column[15] * char_mul}},
		{6	*	offset[15], {6.0f	* char_mul,		char_column[15] * char_mul}},
		{7	*	offset[15], {7.0f	* char_mul,		char_column[15] * char_mul}},
		{8	*	offset[15], {8.0f	* char_mul,		char_column[15] * char_mul}},
		{9	*	offset[15], {9.0f	* char_mul,		char_column[15] * char_mul}},
		{10	*	offset[15], {10.0f	* char_mul,		char_column[15] * char_mul}},
		{11	*	offset[15], {11.0f	* char_mul,		char_column[15] * char_mul}},
		{12	*	offset[15], {12.0f	* char_mul,		char_column[15] * char_mul}},
		{13	*	offset[15], {13.0f	* char_mul,		char_column[15] * char_mul}},
		{14	*	offset[15], {14.0f	* char_mul,		char_column[15] * char_mul}},
		{15	*	offset[15], {15.0f	* char_mul,		char_column[15] * char_mul}},
		{16	*	offset[15], {16.0f	* char_mul,		char_column[15] * char_mul}}
	};

	class Aws_Text
	{
	private:
		Shader shader;
		Array vao;
		Buffer vertices_buf;
		Buffer color_buf;
		Buffer tex_coords_buf;
		Texture atlas;

		Rendered _rendered;
		Vector _psr[3] = {
			{0.0f, 0.0f, 0.0f},
			{1.0f, 1.0f, 1.0f},
			{0.0f, 0.0f, 0.0f}
		};

		std::string _text = "";

		glm::mat4 transform = glm::mat4(1.0f);

	public:
		void Init(uint32_t _vs = LoadShaderFromMemory(text_vs, ShadType::vertex), uint32_t _fs = LoadShaderFromMemory(text_fs, ShadType::fragment)) {
			shader.init();
			shader.attachShader(_vs);
			shader.attachShader(_fs);
			shader.linkShader();

			vao.init();
			vao.bind();

			vertices_buf.init();
			color_buf.init();
			tex_coords_buf.init();
			atlas.init();

			shader.use();

			atlas.uniform(shader.ID, "Texture");

			shader.unuse();

			vertices_buf.bind(BuffType::general, _rendered.data.vertices, 0, 3);
			color_buf.bind(BuffType::general, _rendered.data.color, 1, 4);
			tex_coords_buf.bind(BuffType::general, _rendered.data.texture_coordinates, 2, 2);
			atlas.bind(characters_atlas, GL_REPEAT);

			vao.unbind();
		}

		void Render(glm::mat4 projection = glm::mat4(1.0f), glm::mat4 view = glm::mat4(1.0f)) {
			shader.use();
			vao.bind();

			atlas.bind();

			glUniformMatrix4fv(glGetUniformLocation(shader.ID, "transform"), 1, GL_FALSE, glm::value_ptr(projection * view * transform));

			glDrawArrays(GL_TRIANGLES, 0, _rendered.count * (_rendered.sizeID / 3));

			vao.unbind();
			shader.unuse();
		}

		void SetText(std::string text) {
			if (text != _text)
			{
				_rendered.data.vertices.clear();
				_rendered.data.color.clear();
				_rendered.data.texture_coordinates.clear();
				_rendered.data.normals.clear();

				const char* text_char = text.c_str();

				for (; _rendered.count < sizeof(text_char) / sizeof(text_char[0]); _rendered.count++)
				{
					int text_int = (int)text_char[_rendered.count];

					_rendered.data.vertices.push_back(square.vertices[0] + (float)_rendered.count);
					_rendered.data.vertices.push_back(square.vertices[1] + (float)_rendered.count);
					_rendered.data.vertices.push_back(square.vertices[2] + (float)_rendered.count);

					_rendered.data.vertices.push_back(square.vertices[3] + (float)_rendered.count);
					_rendered.data.vertices.push_back(square.vertices[4] + (float)_rendered.count);
					_rendered.data.vertices.push_back(square.vertices[5] + (float)_rendered.count);

					_rendered.data.vertices.push_back(square.vertices[6] + (float)_rendered.count);
					_rendered.data.vertices.push_back(square.vertices[7] + (float)_rendered.count);
					_rendered.data.vertices.push_back(square.vertices[8] + (float)_rendered.count);

					_rendered.data.vertices.push_back(square.vertices[9] + (float)_rendered.count);
					_rendered.data.vertices.push_back(square.vertices[10] + (float)_rendered.count);
					_rendered.data.vertices.push_back(square.vertices[11] + (float)_rendered.count);

					_rendered.data.vertices.push_back(square.vertices[12] + (float)_rendered.count);
					_rendered.data.vertices.push_back(square.vertices[13] + (float)_rendered.count);
					_rendered.data.vertices.push_back(square.vertices[14] + (float)_rendered.count);

					_rendered.data.vertices.push_back(square.vertices[15] + (float)_rendered.count);
					_rendered.data.vertices.push_back(square.vertices[16] + (float)_rendered.count);
					_rendered.data.vertices.push_back(square.vertices[17] + (float)_rendered.count);

					std::move(square.color.begin(), square.color.end(), std::back_inserter(_rendered.data.color));
					std::move(square.normals.begin(), square.normals.end(), std::back_inserter(_rendered.data.normals));

					_rendered.data.texture_coordinates.push_back((characters_map[text_int].x + char_mul) / 512.0f);
					_rendered.data.texture_coordinates.push_back((characters_map[text_int].y + char_mul) / 512.0f);

					_rendered.data.texture_coordinates.push_back((characters_map[text_int].x) / 512.0f);
					_rendered.data.texture_coordinates.push_back((characters_map[text_int].y + char_mul) / 512.0f);

					_rendered.data.texture_coordinates.push_back((characters_map[text_int].x + char_mul) / 512.0f);
					_rendered.data.texture_coordinates.push_back((characters_map[text_int].y) / 512.0f);

					_rendered.data.texture_coordinates.push_back((characters_map[text_int].x) / 512.0f);
					_rendered.data.texture_coordinates.push_back((characters_map[text_int].y + char_mul) / 512.0f);

					_rendered.data.texture_coordinates.push_back((characters_map[text_int].x + char_mul) / 512.0f);
					_rendered.data.texture_coordinates.push_back((characters_map[text_int].y) / 512.0f);

					_rendered.data.texture_coordinates.push_back((characters_map[text_int].x) / 512.0f);
					_rendered.data.texture_coordinates.push_back((characters_map[text_int].y) / 512.0f);
				}

				vao.bind();

				vertices_buf.bind(BuffType::general, _rendered.data.vertices, 0, 3);
				color_buf.bind(BuffType::general, _rendered.data.color, 1, 4);
				tex_coords_buf.bind(BuffType::general, _rendered.data.texture_coordinates, 2, 2);

				vao.unbind();
				
				_text = text;
			}

		}

		void SetPosition(Vector _values) {
			_psr[0] = _values;

			transform = glm::translate(glm::mat4(1.0), _psr[0].changeV3());
			transform = glm::rotate(transform, glm::radians(_psr[2].x), glm::vec3(1.0f, 0.0f, 0.0f));
			transform = glm::rotate(transform, glm::radians(_psr[2].y), glm::vec3(0.0f, 1.0f, 0.0f));
			transform = glm::rotate(transform, glm::radians(_psr[2].z), glm::vec3(0.0f, 0.0f, 1.0f));
			transform = glm::scale(transform, _psr[1].changeV3());
		}

		void SetScale(Vector _values) {
			_psr[1] = _values;

			transform = glm::translate(glm::mat4(1.0), _psr[0].changeV3());
			transform = glm::rotate(transform, glm::radians(_psr[2].x), glm::vec3(1.0f, 0.0f, 0.0f));
			transform = glm::rotate(transform, glm::radians(_psr[2].y), glm::vec3(0.0f, 1.0f, 0.0f));
			transform = glm::rotate(transform, glm::radians(_psr[2].z), glm::vec3(0.0f, 0.0f, 1.0f));
			transform = glm::scale(transform, _psr[1].changeV3());
		}

		void SetRotation(Vector _values) {
			_psr[2] = _values;

			transform = glm::translate(glm::mat4(1.0), _psr[0].changeV3());
			transform = glm::rotate(transform, glm::radians(_psr[2].x), glm::vec3(1.0f, 0.0f, 0.0f));
			transform = glm::rotate(transform, glm::radians(_psr[2].y), glm::vec3(0.0f, 1.0f, 0.0f));
			transform = glm::rotate(transform, glm::radians(_psr[2].z), glm::vec3(0.0f, 0.0f, 1.0f));
			transform = glm::scale(transform, _psr[1].changeV3());
		}

		void SetColor(Vector _values) {
			if (_rendered.data.color[0] != _values.x && _rendered.data.color[1] != _values.y && _rendered.data.color[2] != _values.z && _rendered.data.color[3] != _values.w)
			{
				for (int i = 0; i < _rendered.count * 6; i++)
				{
					_rendered.data.color[i * 4 + 0] = _values.x;
					_rendered.data.color[i * 4 + 1] = _values.y;
					_rendered.data.color[i * 4 + 2] = _values.z;
					_rendered.data.color[i * 4 + 3] = _values.w;
				}

				vao.bind();

				color_buf.bind(BuffType::general, _rendered.data.color, 1, 4);

				vao.unbind();
			}
		}

		void SetTexture(std::string _path) {
			vao.bind();

			atlas.bind(_path, GL_REPEAT);

			vao.unbind();
		}
	};

	typedef Aws_Text Text;
};