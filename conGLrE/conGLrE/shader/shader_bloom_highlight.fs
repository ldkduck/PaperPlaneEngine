#version 330  
out vec4 color;  
in vec2 TexCoord0;  
 
uniform sampler2D gSampler;  
  
void main()  
{           
    vec3 Color = texture(gSampler, vec2(1-TexCoord0.x,1-TexCoord0.y)).rgb;  
    
	float brightness = dot(Color.rgb, vec3(0.2126, 0.7152, 0.0722));  
    if(brightness > 1.0){  
        color = vec4(Color.rgb, 1.0);   
	}
	else
	{
		color = vec4(Color.rgb * brightness * 0.4, 1.0);
	}	

  
}   