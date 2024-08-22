add_rules("mode.debug", "mode.release")

add_repositories("liteldev-repo https://github.com/LiteLDev/xmake-repo.git")

-- add_requires("levilamina x.x.x") for a specific version
-- add_requires("levilamina develop") to use develop version
-- please note that you should add bdslibrary yourself if using dev version
add_requires("levilamina")
add_requires("sqlite3")
add_requires("legacyremotecall")

if not has_config("vs_runtime") then
    set_runtimes("MD")
end

target("TSEssential") -- Change this to your mod name.
    add_cxflags(
        "/EHa",
        "/utf-8",
        "/W4",
        "/WX",
        "/w44265",
        "/w44289",
        "/w44296",
        "/w45263",
        "/w44738",
        "/w45204"
    )
    add_defines("NOMINMAX", "UNICODE")
    set_optimize("fastest")  -- 最快运行速度的优化
    add_files("src/**.cpp")
    add_files("src/**.rc")
    add_files("src/**.cc")
    add_includedirs("src/includes")
    add_packages("levilamina")
    add_packages("sqlite3")
    add_packages("legacyremotecall")
    add_shflags("/DELAYLOAD:bedrock_server.dll") -- To use symbols provided by SymbolProvider.
    set_exceptions("none") -- To avoid conflicts with /EHa.
    set_kind("shared")
    set_languages("c++23")
    set_symbols("debug")

    after_build(function (target)
        local mod_packer = import("scripts.after_build")

        -- local tag = os.iorun("git describe --tags --abbrev=0 --always")
        local tag = "v1.0.1Beta"
        local major, minor, patch, suffix = tag:match("v(%d+)%.(%d+)%.(%d+)(.*)")
        if not major then
            print("Version tag not found, using 1.0.0")
            major, minor, patch = 1, 0, 0
        end
        local mod_define = {
            modName = target:name(),
            modFile = path.filename(target:targetfile()),
            modVersion = major .. "." .. minor .. "." .. patch,
        }
        
        mod_packer.pack_mod(target,mod_define)
    end)
