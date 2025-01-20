const std = @import("std");
const Editor = @import("editor.zig").Editor;

const c = @cImport({
    @cInclude("term.h");
});

pub fn main() !void {
    const console = std.io.getStdOut();
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    const alloc = gpa.allocator();

    var editor = Editor.new(alloc, console);

    var original_settings: c.struct_termios = undefined;
    _ = c.save_original(&original_settings);

    _ = c.set_raw_mode();
    defer _ = c.restore_mode(&original_settings);

    const stdout = try std.fs.openFileAbsolute("/proc/self/fd/0", .{});
    while (true) {
        const key = editor.get_pressed_key(stdout);
        if (key) |k| {
            switch (k) {
                'h' => try editor.move(1, .Left),
                'l' => try editor.move(1, .Right),
                'k' => try editor.move(1, .Up),
                'j' => try editor.move(1, .Down),
                '\x1b' => break,
                else => {},
            }
        }
    }
}
