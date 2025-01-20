const std = @import("std");

/// ANSI Escape code directions
pub const Direction = enum(u8) {
    Up = 'A',
    Down = 'B',
    Right = 'C',
    Left = 'D',
};

/// Controll Sequence Introducer command (CSI)
/// To issue CSI we use \x1b[ followed:
/// 1. any number (including zero) of "parameter bytes" from 0x30 to 0x3F ( 0-9;:;<=>? )
/// 2. any number of "intermediate bytes" 0x20 to 0x2F ( !"#$%&'()*+,-./ )
/// 3. finally by a single byte from 0x40 to 0x7E ( @A–Z[\]^_`a–z{|}~ )
///
/// Parameters are separated by ; so to skip the middle parameter you would
/// do 1;;3 or just 1;0;3
pub const Editor = struct {
    row: u8 = 0,
    column: u8 = 0,
    rows: u8 = 100,
    cols: u8 = 100,
    // buff: [100][100]u8,

    alloc: std.mem.Allocator,
    console: std.fs.File,

    /// writes to the stdout
    pub fn write(self: *@This(), msg: []const u8) !void {
        try self.console.writeAll(msg);
    }

    pub fn new(alloc: std.mem.Allocator, console: std.fs.File) @This() {
        return @This(){
            .alloc = alloc,
            .console = console,
        };
    }

    /// move uses [n 'DIR'
    /// where n says how much to move
    /// and 'DIR' is A for Up
    ///              B for Down
    ///              C for Right
    ///              D for Left
    /// Example: \x1b[4D -> moves left by 4 chars
    pub fn move(self: *@This(), n: usize, dir: Direction) !void {
        const format = try std.fmt.allocPrint(self.alloc, "\x1b[{d}{c}", .{ n, @intFromEnum(dir) });
        try self.console.writeAll(format);
    }

    pub fn get_pressed_key(self: *@This(), stdin: std.fs.File) ?u8 {
        _ = self;
        var buf: [1]u8 = undefined;
        const read = stdin.read(&buf) catch 0;
        if (read == 1) {
            std.debug.print("Read: {d} for key: {c}\n", .{ read, buf[0] });
            return buf[0];
        }
        return null;
    }
};
