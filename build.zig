const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const exe = b.addExecutable(.{
        .name = "VLTE-c",
        .target = target,
        .optimize = optimize,
    });

    const src_path = b.path("src/");
    exe.linkLibC();

    exe.addCSourceFiles(.{
        .root = src_path,
        .files = &.{
            "main.c",
            "editor.c",
            "raw.c",
        },
        .flags = &.{
            "-std=c99",
            "-pedantic",
            "-Werror",
            "-Wall",
            "-Wextra",
            "-g",
            "-Wshadow",
            "-Wformat=2",
            "-Wfloat-equal",
            "-Wconversion",
            "-Wunreachable-code",
            "-Wundef",
            "-Wcast-align",
            "-Wpointer-arith",
            "-Wwrite-strings",
            "-Wredundant-decls",
            "-Wimplicit-fallthrough",
            "-Wstrict-overflow",
            "-Wswitch-default",
            "-Wswitch-enum",
            "-Winit-self",
            "-Wmissing-include-dirs",
            "-Winline",
            "-Wstack-protector",
            "-fstack-protector-strong",
        },
    });

    b.installArtifact(exe);

    const run_cmd = b.addRunArtifact(exe);
    run_cmd.step.dependOn(b.getInstallStep());
    if (b.args) |args| {
        run_cmd.addArgs(args);
    }

    const run_step = b.step("run", "Run the app");
    run_step.dependOn(&run_cmd.step);
}
