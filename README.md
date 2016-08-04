# chapter09
细分着色器<br/>

绘制茶壶，只有半个，实现 一步一步细分<br/>
细分控制部分<br/>
//---------------<br/>
    gl_TessLevelInner[0] = Inner;<br/>
    gl_TessLevelInner[1] = Inner;<br/>
    gl_TessLevelOuter[0] = Outer;<br/>
    gl_TessLevelOuter[1] = Outer;<br/>
    gl_TessLevelOuter[2] = Outer;<br/>
    gl_TessLevelOuter[3] = Outer;<br/>
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;<br/>
    ------------//<br/>
细分计算部分<br/>
//---------------<br/>
vec4  pos = vec4( 0.0 );<br/>
    float  u = gl_TessCoord.x;<br/>
    float  v = gl_TessCoord.y;<br/>
    for ( int j = 0; j < 4; ++j ) {<br/>
        for ( int i = 0; i < 4; ++i ) {<br/>
            pos += B( i, u ) * B( j, v ) * gl_in[4*j+i].gl_Position;<br/>
        }<br/>
    }<br/>
    gl_Position = P * MV * pos;<br/>
---------------//<br/>
