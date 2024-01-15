varying highp vec3 vert;
varying highp vec3 vertNormal;
uniform highp vec3 lightPos;
varying vec4 fragColor; 

void main() {
    highp vec3 LightDir = normalize(lightPos - vert);
    vec3 N = normalize(vertNormal);
    highp float NL = max(dot(N, -LightDir), 0.0);

    float intensity = pow(max(0.0, dot(LightDir, normalize(vert))), 2.0);
    vec3 rayColor = vec3(1.0, 0.4, 0) * intensity;

    highp vec3 color = fragColor.rgb; 
    highp vec3 col = clamp(color * 0.2 + color * 0.8 * NL + rayColor, 0.0, 1.0);
    gl_FragColor = vec4(col, 1.0);
}
