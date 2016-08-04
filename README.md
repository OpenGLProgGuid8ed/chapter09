# chapter09
细分着色器

绘制茶壶，只有半个，实现 一步一步细分
细分控制部分
//---------------
    gl_TessLevelInner[0] = Inner;
    gl_TessLevelInner[1] = Inner;
    gl_TessLevelOuter[0] = Outer;
    gl_TessLevelOuter[1] = Outer;
    gl_TessLevelOuter[2] = Outer;
    gl_TessLevelOuter[3] = Outer;
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
    ------------//
细分计算部分
//---------------
vec4  pos = vec4( 0.0 );
    float  u = gl_TessCoord.x;
    float  v = gl_TessCoord.y;
    for ( int j = 0; j < 4; ++j ) {
        for ( int i = 0; i < 4; ++i ) {
            pos += B( i, u ) * B( j, v ) * gl_in[4*j+i].gl_Position;
        }
    }
    gl_Position = P * MV * pos;
---------------//
