#version 120

uniform sampler2DRect tex0;

uniform float squared_threshold;
uniform float squared_smooth;

varying vec2 texCoordVarying;

void main()
{
    // gl_FragCoord contains the window relative coordinate for the fragment.
    // we use gl_FragCoord.x position to control the red color value.
    // we use gl_FragCoord.y position to control the green color value.
    // please note that all r, g, b, a values are between 0 and 1.

    vec4 color;
    vec4 outputColor;
    color =  texture2DRect(tex0, texCoordVarying );
    float squared_distance = dot(color,color);
    
    if (squared_distance > squared_threshold + squared_smooth )
    {
     outputColor = color;
    }
    else if (squared_distance > squared_threshold )
    {
        float alphaValue = (squared_distance - squared_threshold ) / squared_smooth;
        outputColor = vec4(color.r, color.g, color.b, alphaValue);

    }
    else    
    {
     outputColor = vec4(0, 0, 0, 0);
    }


    gl_FragColor = outputColor;


}

