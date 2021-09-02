#define TL_IMPL
#define TL_MAIN
#define TGRAPHICS_IMPL
#include <tl/common.h>
#include <tl/window.h>
#include <tgraphics/tgraphics.h>

using namespace tl;
namespace tg = tgraphics;

s32 tl_main(Span<Span<utf8>> arguments) {

	auto window = create_window({
		.title = u8"Drawt"s,
		.on_create = [](Window &window) {
			if (!tg::init(tg::GraphicsApi_opengl, {.window = window.handle, .debug = true})) {
				print("tg::init failed\n");
				debug_break();
			}
		},
		.on_draw = [](Window &window) {
			tg::present();
		}
	});

	while (update(window)) {
	}

	return 0;
}
