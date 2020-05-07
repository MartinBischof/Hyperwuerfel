#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

attribute vec3 a_position;
attribute vec3 a_color;
attribute vec3 a_normals;

varying vec4 v_color;

uniform mat4 u_modelViewProjMatrix;

void main(void)
{
    gl_Position = u_modelViewProjMatrix*vec4(a_position,1.0f);
    v_color = vec4(a_normals,1.0f);
}
