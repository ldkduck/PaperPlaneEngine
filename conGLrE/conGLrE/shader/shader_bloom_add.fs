#version 330  
out vec4 color;  
in vec2 TexCoord0;  
 
uniform sampler2D gSrcSampler;  
uniform sampler2D gBlurSampler;

 
void main()  
{           
    vec3 hdrColor = texture(gSrcSampler, vec2(1-TexCoord0.x,1-TexCoord0.y)).rgb;        
    vec3 bloomColor = texture(gBlurSampler, vec2(1-TexCoord0.x,1-TexCoord0.y)).rgb;
    hdrColor += bloomColor;  
    color = vec4(hdrColor, 1.0f);
  
}   