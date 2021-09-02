#define TL_IMPL
#define TL_MAIN
#define TGRAPHICS_IMPL
#include <tl/common.h>
#include <tl/window.h>
#include <tgraphics/tgraphics.h>

using namespace tl;
namespace tg = tgraphics;

tg::Shader *test_shader;

s32 tl_main(Span<Span<utf8>> arguments) {

	auto window = create_window({
		.title = u8"Drawt"s,
		.on_create = [](Window &window) {
			if (!tg::init(tg::GraphicsApi_opengl, {.window = window.handle, .debug = true})) {
				print("tg::init failed\n");
				debug_break();
			}

			test_shader = tg::create_shader(u8R"(

#ifdef VERTEX_SHADER
void main() {
	vec2 positions[] = vec2[](
		vec2( 0.0,  0.5),
		vec2(-0.5, -0.5),
		vec2( 0.5, -0.5)
	);
	gl_Position = vec4(positions[gl_VertexID], 0, 1);
}
#endif

#ifdef FRAGMENT_SHADER
out vec4 fragment_color;
void main() {
	fragment_color = vec4(1);
}
#endif

)"s);
		},
		.on_draw = [](Window &window) {

			tg::set_render_target(tg::back_buffer);
			tg::clear(tg::back_buffer, tg::ClearFlags_color | tg::ClearFlags_depth, {}, 1);
			tg::set_viewport(window.client_size);

			tg::set_shader(test_shader);
			tg::draw(3);

			tg::present();
		}
	});

	while (update(window)) {
	}

	return 0;
}
