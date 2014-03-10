//
//  Shader.fsh
//  问题
//
//  Created by Chao Wu on 3/9/14.
//  Copyright (c) 2014 Chao Wu. All rights reserved.
//

varying lowp vec4 colorVarying;

void main()
{
    gl_FragColor = colorVarying;
}
