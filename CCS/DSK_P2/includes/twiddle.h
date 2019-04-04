/* -------------------------------------------------------------------- */
/*  Automatically generated twiddle-factor array.                       */
/*      Number of points:    1024                                        */
/*      Appropriate FFTs:    DSPF_sp_cfftr4_dif                         */
/*      Required alignment:  8 byte (double word)                       */
/* -------------------------------------------------------------------- */
/*  NOTE:  It is suggested that this array be aligned to an odd         */
/*  starting bank to reduce bank conflicts.  This can be achieved by    */
/*  using the DATA_MEM_BANK pragma.  Please see the TMS320C6000         */
/*  Optimizing C Compiler Reference (SPRU187E) for details on using     */
/*  "#pragma DATA_MEM_BANK".                                            */
/* -------------------------------------------------------------------- */

#ifdef _TMS320C6400
# pragma DATA_MEM_BANK(w, 1);  /* C64x has 32-bit banks */
#else
# pragma DATA_MEM_BANK(w, 2);  /* C62x and C67x have 16-bit banks */
#endif

float w[2 * 768] =
{
     1.000000,  0.000000,  0.999981,  0.006136,  0.999925,  0.012272,  0.999831,  0.018407,
     0.999699,  0.024541,  0.999529,  0.030675,  0.999322,  0.036807,  0.999078,  0.042938,
     0.998795,  0.049068,  0.998476,  0.055195,  0.998118,  0.061321,  0.997723,  0.067444,
     0.997290,  0.073565,  0.996820,  0.079682,  0.996313,  0.085797,  0.995767,  0.091909,
     0.995185,  0.098017,  0.994565,  0.104122,  0.993907,  0.110222,  0.993212,  0.116319,
     0.992480,  0.122411,  0.991710,  0.128498,  0.990903,  0.134581,  0.990058,  0.140658,
     0.989177,  0.146730,  0.988258,  0.152797,  0.987301,  0.158858,  0.986308,  0.164913,
     0.985278,  0.170962,  0.984210,  0.177004,  0.983105,  0.183040,  0.981964,  0.189069,
     0.980785,  0.195090,  0.979570,  0.201105,  0.978317,  0.207111,  0.977028,  0.213110,
     0.975702,  0.219101,  0.974339,  0.225084,  0.972940,  0.231058,  0.971504,  0.237024,
     0.970031,  0.242980,  0.968522,  0.248928,  0.966976,  0.254866,  0.965394,  0.260794,
     0.963776,  0.266713,  0.962121,  0.272621,  0.960431,  0.278520,  0.958703,  0.284408,
     0.956940,  0.290285,  0.955141,  0.296151,  0.953306,  0.302006,  0.951435,  0.307850,
     0.949528,  0.313682,  0.947586,  0.319502,  0.945607,  0.325310,  0.943593,  0.331106,
     0.941544,  0.336890,  0.939459,  0.342661,  0.937339,  0.348419,  0.935184,  0.354164,
     0.932993,  0.359895,  0.930767,  0.365613,  0.928506,  0.371317,  0.926210,  0.377007,
     0.923880,  0.382683,  0.921514,  0.388345,  0.919114,  0.393992,  0.916679,  0.399624,
     0.914210,  0.405241,  0.911706,  0.410843,  0.909168,  0.416430,  0.906596,  0.422000,
     0.903989,  0.427555,  0.901349,  0.433094,  0.898674,  0.438616,  0.895966,  0.444122,
     0.893224,  0.449611,  0.890449,  0.455084,  0.887640,  0.460539,  0.884797,  0.465977,
     0.881921,  0.471397,  0.879012,  0.476799,  0.876070,  0.482184,  0.873095,  0.487550,
     0.870087,  0.492898,  0.867046,  0.498228,  0.863973,  0.503538,  0.860867,  0.508830,
     0.857729,  0.514103,  0.854558,  0.519356,  0.851355,  0.524590,  0.848120,  0.529804,
     0.844854,  0.534998,  0.841555,  0.540171,  0.838225,  0.545325,  0.834863,  0.550458,
     0.831470,  0.555570,  0.828045,  0.560662,  0.824589,  0.565732,  0.821102,  0.570781,
     0.817585,  0.575808,  0.814036,  0.580814,  0.810457,  0.585798,  0.806848,  0.590760,
     0.803208,  0.595699,  0.799537,  0.600616,  0.795837,  0.605511,  0.792107,  0.610383,
     0.788346,  0.615232,  0.784557,  0.620057,  0.780737,  0.624860,  0.776888,  0.629638,
     0.773010,  0.634393,  0.769103,  0.639124,  0.765167,  0.643832,  0.761202,  0.648514,
     0.757209,  0.653173,  0.753187,  0.657807,  0.749136,  0.662416,  0.745058,  0.667000,
     0.740951,  0.671559,  0.736817,  0.676093,  0.732654,  0.680601,  0.728464,  0.685084,
     0.724247,  0.689541,  0.720003,  0.693971,  0.715731,  0.698376,  0.711432,  0.702755,
     0.707107,  0.707107,  0.702755,  0.711432,  0.698376,  0.715731,  0.693971,  0.720003,
     0.689541,  0.724247,  0.685084,  0.728464,  0.680601,  0.732654,  0.676093,  0.736817,
     0.671559,  0.740951,  0.667000,  0.745058,  0.662416,  0.749136,  0.657807,  0.753187,
     0.653173,  0.757209,  0.648514,  0.761202,  0.643832,  0.765167,  0.639124,  0.769103,
     0.634393,  0.773010,  0.629638,  0.776888,  0.624860,  0.780737,  0.620057,  0.784557,
     0.615232,  0.788346,  0.610383,  0.792107,  0.605511,  0.795837,  0.600616,  0.799537,
     0.595699,  0.803208,  0.590760,  0.806848,  0.585798,  0.810457,  0.580814,  0.814036,
     0.575808,  0.817585,  0.570781,  0.821102,  0.565732,  0.824589,  0.560662,  0.828045,
     0.555570,  0.831470,  0.550458,  0.834863,  0.545325,  0.838225,  0.540171,  0.841555,
     0.534998,  0.844854,  0.529804,  0.848120,  0.524590,  0.851355,  0.519356,  0.854558,
     0.514103,  0.857729,  0.508830,  0.860867,  0.503538,  0.863973,  0.498228,  0.867046,
     0.492898,  0.870087,  0.487550,  0.873095,  0.482184,  0.876070,  0.476799,  0.879012,
     0.471397,  0.881921,  0.465977,  0.884797,  0.460539,  0.887640,  0.455084,  0.890449,
     0.449611,  0.893224,  0.444122,  0.895966,  0.438616,  0.898674,  0.433094,  0.901349,
     0.427555,  0.903989,  0.422000,  0.906596,  0.416430,  0.909168,  0.410843,  0.911706,
     0.405241,  0.914210,  0.399624,  0.916679,  0.393992,  0.919114,  0.388345,  0.921514,
     0.382683,  0.923880,  0.377007,  0.926210,  0.371317,  0.928506,  0.365613,  0.930767,
     0.359895,  0.932993,  0.354164,  0.935184,  0.348419,  0.937339,  0.342661,  0.939459,
     0.336890,  0.941544,  0.331106,  0.943593,  0.325310,  0.945607,  0.319502,  0.947586,
     0.313682,  0.949528,  0.307850,  0.951435,  0.302006,  0.953306,  0.296151,  0.955141,
     0.290285,  0.956940,  0.284408,  0.958703,  0.278520,  0.960431,  0.272621,  0.962121,
     0.266713,  0.963776,  0.260794,  0.965394,  0.254866,  0.966976,  0.248928,  0.968522,
     0.242980,  0.970031,  0.237024,  0.971504,  0.231058,  0.972940,  0.225084,  0.974339,
     0.219101,  0.975702,  0.213110,  0.977028,  0.207111,  0.978317,  0.201105,  0.979570,
     0.195090,  0.980785,  0.189069,  0.981964,  0.183040,  0.983105,  0.177004,  0.984210,
     0.170962,  0.985278,  0.164913,  0.986308,  0.158858,  0.987301,  0.152797,  0.988258,
     0.146730,  0.989177,  0.140658,  0.990058,  0.134581,  0.990903,  0.128498,  0.991710,
     0.122411,  0.992480,  0.116319,  0.993212,  0.110222,  0.993907,  0.104122,  0.994565,
     0.098017,  0.995185,  0.091909,  0.995767,  0.085797,  0.996313,  0.079682,  0.996820,
     0.073565,  0.997290,  0.067444,  0.997723,  0.061321,  0.998118,  0.055195,  0.998476,
     0.049068,  0.998795,  0.042938,  0.999078,  0.036807,  0.999322,  0.030675,  0.999529,
     0.024541,  0.999699,  0.018407,  0.999831,  0.012272,  0.999925,  0.006136,  0.999981,
     0.000000,  1.000000, -0.006136,  0.999981, -0.012272,  0.999925, -0.018407,  0.999831,
    -0.024541,  0.999699, -0.030675,  0.999529, -0.036807,  0.999322, -0.042938,  0.999078,
    -0.049068,  0.998795, -0.055195,  0.998476, -0.061321,  0.998118, -0.067444,  0.997723,
    -0.073565,  0.997290, -0.079682,  0.996820, -0.085797,  0.996313, -0.091909,  0.995767,
    -0.098017,  0.995185, -0.104122,  0.994565, -0.110222,  0.993907, -0.116319,  0.993212,
    -0.122411,  0.992480, -0.128498,  0.991710, -0.134581,  0.990903, -0.140658,  0.990058,
    -0.146730,  0.989177, -0.152797,  0.988258, -0.158858,  0.987301, -0.164913,  0.986308,
    -0.170962,  0.985278, -0.177004,  0.984210, -0.183040,  0.983105, -0.189069,  0.981964,
    -0.195090,  0.980785, -0.201105,  0.979570, -0.207111,  0.978317, -0.213110,  0.977028,
    -0.219101,  0.975702, -0.225084,  0.974339, -0.231058,  0.972940, -0.237024,  0.971504,
    -0.242980,  0.970031, -0.248928,  0.968522, -0.254866,  0.966976, -0.260794,  0.965394,
    -0.266713,  0.963776, -0.272621,  0.962121, -0.278520,  0.960431, -0.284408,  0.958703,
    -0.290285,  0.956940, -0.296151,  0.955141, -0.302006,  0.953306, -0.307850,  0.951435,
    -0.313682,  0.949528, -0.319502,  0.947586, -0.325310,  0.945607, -0.331106,  0.943593,
    -0.336890,  0.941544, -0.342661,  0.939459, -0.348419,  0.937339, -0.354164,  0.935184,
    -0.359895,  0.932993, -0.365613,  0.930767, -0.371317,  0.928506, -0.377007,  0.926210,
    -0.382683,  0.923880, -0.388345,  0.921514, -0.393992,  0.919114, -0.399624,  0.916679,
    -0.405241,  0.914210, -0.410843,  0.911706, -0.416430,  0.909168, -0.422000,  0.906596,
    -0.427555,  0.903989, -0.433094,  0.901349, -0.438616,  0.898674, -0.444122,  0.895966,
    -0.449611,  0.893224, -0.455084,  0.890449, -0.460539,  0.887640, -0.465977,  0.884797,
    -0.471397,  0.881921, -0.476799,  0.879012, -0.482184,  0.876070, -0.487550,  0.873095,
    -0.492898,  0.870087, -0.498228,  0.867046, -0.503538,  0.863973, -0.508830,  0.860867,
    -0.514103,  0.857729, -0.519356,  0.854558, -0.524590,  0.851355, -0.529804,  0.848120,
    -0.534998,  0.844854, -0.540171,  0.841555, -0.545325,  0.838225, -0.550458,  0.834863,
    -0.555570,  0.831470, -0.560662,  0.828045, -0.565732,  0.824589, -0.570781,  0.821102,
    -0.575808,  0.817585, -0.580814,  0.814036, -0.585798,  0.810457, -0.590760,  0.806848,
    -0.595699,  0.803208, -0.600616,  0.799537, -0.605511,  0.795837, -0.610383,  0.792107,
    -0.615232,  0.788346, -0.620057,  0.784557, -0.624860,  0.780737, -0.629638,  0.776888,
    -0.634393,  0.773010, -0.639124,  0.769103, -0.643832,  0.765167, -0.648514,  0.761202,
    -0.653173,  0.757209, -0.657807,  0.753187, -0.662416,  0.749136, -0.667000,  0.745058,
    -0.671559,  0.740951, -0.676093,  0.736817, -0.680601,  0.732654, -0.685084,  0.728464,
    -0.689541,  0.724247, -0.693971,  0.720003, -0.698376,  0.715731, -0.702755,  0.711432,
    -0.707107,  0.707107, -0.711432,  0.702755, -0.715731,  0.698376, -0.720003,  0.693971,
    -0.724247,  0.689541, -0.728464,  0.685084, -0.732654,  0.680601, -0.736817,  0.676093,
    -0.740951,  0.671559, -0.745058,  0.667000, -0.749136,  0.662416, -0.753187,  0.657807,
    -0.757209,  0.653173, -0.761202,  0.648514, -0.765167,  0.643832, -0.769103,  0.639124,
    -0.773010,  0.634393, -0.776888,  0.629638, -0.780737,  0.624860, -0.784557,  0.620057,
    -0.788346,  0.615232, -0.792107,  0.610383, -0.795837,  0.605511, -0.799537,  0.600616,
    -0.803208,  0.595699, -0.806848,  0.590760, -0.810457,  0.585798, -0.814036,  0.580814,
    -0.817585,  0.575808, -0.821102,  0.570781, -0.824589,  0.565732, -0.828045,  0.560662,
    -0.831470,  0.555570, -0.834863,  0.550458, -0.838225,  0.545325, -0.841555,  0.540171,
    -0.844854,  0.534998, -0.848120,  0.529804, -0.851355,  0.524590, -0.854558,  0.519356,
    -0.857729,  0.514103, -0.860867,  0.508830, -0.863973,  0.503538, -0.867046,  0.498228,
    -0.870087,  0.492898, -0.873095,  0.487550, -0.876070,  0.482184, -0.879012,  0.476799,
    -0.881921,  0.471397, -0.884797,  0.465977, -0.887640,  0.460539, -0.890449,  0.455084,
    -0.893224,  0.449611, -0.895966,  0.444122, -0.898674,  0.438616, -0.901349,  0.433094,
    -0.903989,  0.427555, -0.906596,  0.422000, -0.909168,  0.416430, -0.911706,  0.410843,
    -0.914210,  0.405241, -0.916679,  0.399624, -0.919114,  0.393992, -0.921514,  0.388345,
    -0.923880,  0.382683, -0.926210,  0.377007, -0.928506,  0.371317, -0.930767,  0.365613,
    -0.932993,  0.359895, -0.935184,  0.354164, -0.937339,  0.348419, -0.939459,  0.342661,
    -0.941544,  0.336890, -0.943593,  0.331106, -0.945607,  0.325310, -0.947586,  0.319502,
    -0.949528,  0.313682, -0.951435,  0.307850, -0.953306,  0.302006, -0.955141,  0.296151,
    -0.956940,  0.290285, -0.958703,  0.284408, -0.960431,  0.278520, -0.962121,  0.272621,
    -0.963776,  0.266713, -0.965394,  0.260794, -0.966976,  0.254866, -0.968522,  0.248928,
    -0.970031,  0.242980, -0.971504,  0.237024, -0.972940,  0.231058, -0.974339,  0.225084,
    -0.975702,  0.219101, -0.977028,  0.213110, -0.978317,  0.207111, -0.979570,  0.201105,
    -0.980785,  0.195090, -0.981964,  0.189069, -0.983105,  0.183040, -0.984210,  0.177004,
    -0.985278,  0.170962, -0.986308,  0.164913, -0.987301,  0.158858, -0.988258,  0.152797,
    -0.989177,  0.146730, -0.990058,  0.140658, -0.990903,  0.134581, -0.991710,  0.128498,
    -0.992480,  0.122411, -0.993212,  0.116319, -0.993907,  0.110222, -0.994565,  0.104122,
    -0.995185,  0.098017, -0.995767,  0.091909, -0.996313,  0.085797, -0.996820,  0.079682,
    -0.997290,  0.073565, -0.997723,  0.067444, -0.998118,  0.061321, -0.998476,  0.055195,
    -0.998795,  0.049068, -0.999078,  0.042938, -0.999322,  0.036807, -0.999529,  0.030675,
    -0.999699,  0.024541, -0.999831,  0.018407, -0.999925,  0.012272, -0.999981,  0.006136,
    -1.000000, -0.000000, -0.999981, -0.006136, -0.999925, -0.012272, -0.999831, -0.018407,
    -0.999699, -0.024541, -0.999529, -0.030675, -0.999322, -0.036807, -0.999078, -0.042938,
    -0.998795, -0.049068, -0.998476, -0.055195, -0.998118, -0.061321, -0.997723, -0.067444,
    -0.997290, -0.073565, -0.996820, -0.079682, -0.996313, -0.085797, -0.995767, -0.091909,
    -0.995185, -0.098017, -0.994565, -0.104122, -0.993907, -0.110222, -0.993212, -0.116319,
    -0.992480, -0.122411, -0.991710, -0.128498, -0.990903, -0.134581, -0.990058, -0.140658,
    -0.989177, -0.146730, -0.988258, -0.152797, -0.987301, -0.158858, -0.986308, -0.164913,
    -0.985278, -0.170962, -0.984210, -0.177004, -0.983105, -0.183040, -0.981964, -0.189069,
    -0.980785, -0.195090, -0.979570, -0.201105, -0.978317, -0.207111, -0.977028, -0.213110,
    -0.975702, -0.219101, -0.974339, -0.225084, -0.972940, -0.231058, -0.971504, -0.237024,
    -0.970031, -0.242980, -0.968522, -0.248928, -0.966976, -0.254866, -0.965394, -0.260794,
    -0.963776, -0.266713, -0.962121, -0.272621, -0.960431, -0.278520, -0.958703, -0.284408,
    -0.956940, -0.290285, -0.955141, -0.296151, -0.953306, -0.302006, -0.951435, -0.307850,
    -0.949528, -0.313682, -0.947586, -0.319502, -0.945607, -0.325310, -0.943593, -0.331106,
    -0.941544, -0.336890, -0.939459, -0.342661, -0.937339, -0.348419, -0.935184, -0.354164,
    -0.932993, -0.359895, -0.930767, -0.365613, -0.928506, -0.371317, -0.926210, -0.377007,
    -0.923880, -0.382683, -0.921514, -0.388345, -0.919114, -0.393992, -0.916679, -0.399624,
    -0.914210, -0.405241, -0.911706, -0.410843, -0.909168, -0.416430, -0.906596, -0.422000,
    -0.903989, -0.427555, -0.901349, -0.433094, -0.898674, -0.438616, -0.895966, -0.444122,
    -0.893224, -0.449611, -0.890449, -0.455084, -0.887640, -0.460539, -0.884797, -0.465977,
    -0.881921, -0.471397, -0.879012, -0.476799, -0.876070, -0.482184, -0.873095, -0.487550,
    -0.870087, -0.492898, -0.867046, -0.498228, -0.863973, -0.503538, -0.860867, -0.508830,
    -0.857729, -0.514103, -0.854558, -0.519356, -0.851355, -0.524590, -0.848120, -0.529804,
    -0.844854, -0.534998, -0.841555, -0.540171, -0.838225, -0.545325, -0.834863, -0.550458,
    -0.831470, -0.555570, -0.828045, -0.560662, -0.824589, -0.565732, -0.821102, -0.570781,
    -0.817585, -0.575808, -0.814036, -0.580814, -0.810457, -0.585798, -0.806848, -0.590760,
    -0.803208, -0.595699, -0.799537, -0.600616, -0.795837, -0.605511, -0.792107, -0.610383,
    -0.788346, -0.615232, -0.784557, -0.620057, -0.780737, -0.624860, -0.776888, -0.629638,
    -0.773010, -0.634393, -0.769103, -0.639124, -0.765167, -0.643832, -0.761202, -0.648514,
    -0.757209, -0.653173, -0.753187, -0.657807, -0.749136, -0.662416, -0.745058, -0.667000,
    -0.740951, -0.671559, -0.736817, -0.676093, -0.732654, -0.680601, -0.728464, -0.685084,
    -0.724247, -0.689541, -0.720003, -0.693971, -0.715731, -0.698376, -0.711432, -0.702755,
    -0.707107, -0.707107, -0.702755, -0.711432, -0.698376, -0.715731, -0.693971, -0.720003,
    -0.689541, -0.724247, -0.685084, -0.728464, -0.680601, -0.732654, -0.676093, -0.736817,
    -0.671559, -0.740951, -0.667000, -0.745058, -0.662416, -0.749136, -0.657807, -0.753187,
    -0.653173, -0.757209, -0.648514, -0.761202, -0.643832, -0.765167, -0.639124, -0.769103,
    -0.634393, -0.773010, -0.629638, -0.776888, -0.624860, -0.780737, -0.620057, -0.784557,
    -0.615232, -0.788346, -0.610383, -0.792107, -0.605511, -0.795837, -0.600616, -0.799537,
    -0.595699, -0.803208, -0.590760, -0.806848, -0.585798, -0.810457, -0.580814, -0.814036,
    -0.575808, -0.817585, -0.570781, -0.821102, -0.565732, -0.824589, -0.560662, -0.828045,
    -0.555570, -0.831470, -0.550458, -0.834863, -0.545325, -0.838225, -0.540171, -0.841555,
    -0.534998, -0.844854, -0.529804, -0.848120, -0.524590, -0.851355, -0.519356, -0.854558,
    -0.514103, -0.857729, -0.508830, -0.860867, -0.503538, -0.863973, -0.498228, -0.867046,
    -0.492898, -0.870087, -0.487550, -0.873095, -0.482184, -0.876070, -0.476799, -0.879012,
    -0.471397, -0.881921, -0.465977, -0.884797, -0.460539, -0.887640, -0.455084, -0.890449,
    -0.449611, -0.893224, -0.444122, -0.895966, -0.438616, -0.898674, -0.433094, -0.901349,
    -0.427555, -0.903989, -0.422000, -0.906596, -0.416430, -0.909168, -0.410843, -0.911706,
    -0.405241, -0.914210, -0.399624, -0.916679, -0.393992, -0.919114, -0.388345, -0.921514,
    -0.382683, -0.923880, -0.377007, -0.926210, -0.371317, -0.928506, -0.365613, -0.930767,
    -0.359895, -0.932993, -0.354164, -0.935184, -0.348419, -0.937339, -0.342661, -0.939459,
    -0.336890, -0.941544, -0.331106, -0.943593, -0.325310, -0.945607, -0.319502, -0.947586,
    -0.313682, -0.949528, -0.307850, -0.951435, -0.302006, -0.953306, -0.296151, -0.955141,
    -0.290285, -0.956940, -0.284408, -0.958703, -0.278520, -0.960431, -0.272621, -0.962121,
    -0.266713, -0.963776, -0.260794, -0.965394, -0.254866, -0.966976, -0.248928, -0.968522,
    -0.242980, -0.970031, -0.237024, -0.971504, -0.231058, -0.972940, -0.225084, -0.974339,
    -0.219101, -0.975702, -0.213110, -0.977028, -0.207111, -0.978317, -0.201105, -0.979570,
    -0.195090, -0.980785, -0.189069, -0.981964, -0.183040, -0.983105, -0.177004, -0.984210,
    -0.170962, -0.985278, -0.164913, -0.986308, -0.158858, -0.987301, -0.152797, -0.988258,
    -0.146730, -0.989177, -0.140658, -0.990058, -0.134581, -0.990903, -0.128498, -0.991710,
    -0.122411, -0.992480, -0.116319, -0.993212, -0.110222, -0.993907, -0.104122, -0.994565,
    -0.098017, -0.995185, -0.091909, -0.995767, -0.085797, -0.996313, -0.079682, -0.996820,
    -0.073565, -0.997290, -0.067444, -0.997723, -0.061321, -0.998118, -0.055195, -0.998476,
    -0.049068, -0.998795, -0.042938, -0.999078, -0.036807, -0.999322, -0.030675, -0.999529,
    -0.024541, -0.999699, -0.018407, -0.999831, -0.012272, -0.999925, -0.006136, -0.999981
};