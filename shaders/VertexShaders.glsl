attribute vec4 posAttr;
attribute vec4 colAttr; 
attribute vec3 normalAttr;
attribute vec4 vertex;
attribute vec3 normal;

varying vec3 vert;
varying vec3 vertNormal;
varying vec4 fragColor; 

uniform mat3 normalMatrix;
uniform highp mat4 u_ProjMatrix;
uniform highp mat4 u_modelMatrix;
uniform highp mat4 u_viewMatrix;



void main() {
    vert = posAttr.xyz;
    vertNormal = normalAttr;
    fragColor = colAttr;
    
    gl_Position = u_ProjMatrix * u_modelMatrix * u_viewMatrix * posAttr ;
   

}

