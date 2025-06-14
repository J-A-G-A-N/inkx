const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const exe = b.addExecutable(.{
        .name = "inkx",
        .target = target,
        .optimize = optimize,
    });

    const flags = &[_][]const u8{
        "-Werror",
        "-march=native",
        "-O3",
        "-ffast-math",
    };

    const c_sources = &[_][]const u8{
        "src/main.c",
        "src/ferror/ferror.c",
        "src/io/io.c",
        "src/io/render_txt.c",
        "src/data/gap_buffer/gap_buffer.c",
        "src/data/text_struct/text_struct.c",
        "src/data/dynamic_array/dynamicarray.c",
    };

    exe.addCSourceFiles(.{
        .files = c_sources,
        .flags = flags,
    });
    exe.linkLibC();
    exe.linkSystemLibrary("ncurses");

    b.installArtifact(exe);

    // Create run step
    const run_cmd = b.addRunArtifact(exe);
    run_cmd.step.dependOn(b.getInstallStep());

    // Add run step as top level
    const run_step = b.step("run", "Run the app");
    run_step.dependOn(&run_cmd.step);
    if (b.args) |args| {
        run_cmd.addArgs(args);
    }
    //run_cmd.addArgs(&[_][]const u8{"arg1"});

    // Clean step
    const clean_step = b.step("clean", "Clean build artifacts");
    clean_step.dependOn(&b.addRemoveDirTree(b.path("zig-out")).step);
    clean_step.dependOn(&b.addRemoveDirTree(b.path("zig-cache")).step);
}
