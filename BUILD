load("@io_bazel_rules_go//go:def.bzl", "go_library")

go_library(
    name = "go_default_library",
    srcs = [
        "display.go",
        "display.h",
        "display_darwin.c",
        "display_linux.c",
        "doc.go",
        "event.go",
        "keys.go",
    ],
    cgo = True,
    clinkopts = select({
        "@io_bazel_rules_go//go/platform:darwin": [
            "-framework GLUT -framework OpenGL",
        ],
        "@io_bazel_rules_go//go/platform:linux": [
            "-lGL -lSDL2",
        ],
        "@io_bazel_rules_go//go/platform:windows": [
            "-lopengl32 -lSDL2",
        ],
        "//conditions:default": [],
    }),
    copts = select({
        "@io_bazel_rules_go//go/platform:darwin": [
            "-Wno-deprecated-declarations",
        ],
        "//conditions:default": [],
    }),
    importpath = "aqwari.net/exp/display",
    visibility = ["//visibility:public"],
)
