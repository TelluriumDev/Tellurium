add_rules("mode.debug", "mode.release")

add_repositories("liteldev-repo https://github.com/LiteLDev/xmake-repo.git")

add_requires("levilamina")
add_requires("sqlite3")
add_requires("nlohmann_json")
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
    add_files("src/**.cpp")
    add_files("src/**.rc")
    add_includedirs("src/includes")
    add_packages("levilamina")
    add_packages("nlohmann_json")
    add_packages("sqlite3")
    add_packages("legacyremotecall")
    add_shflags("/DELAYLOAD:bedrock_server.dll")
    set_exceptions("none")
    set_kind("shared")
    set_languages("c++23")
    set_symbols("debug")
    if is_mode("release") then
        set_optimize("fastest")
    end
    if is_mode("debug") then
        set_symbols("debug", "edit")
    end

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


    on_load(function (target)
        local tag = os.iorun("git describe --tags --abbrev=0 --always")
        local major, minor, patch, suffix = tag:match("v(%d+)%.(%d+)%.(%d+)(.*)")
        if not major then
            print("Failed to parse version tag, using 0.0.0")
            major, minor, patch = 0, 0, 0
        end
        if suffix then
            prerelease = suffix:match("-(.*)")
            if prerelease then
                prerelease = prerelease:gsub("\n", "")
            end
            if prerelease then
                target:set("configvar", "TSET_VERSION_PRERELEASE", prerelease)
            end
        end
        target:set("configvar", "TSET_VERSION_MAJOR", major)
        print(major,minor,patch)
        target:set("configvar", "TSET_VERSION_MINOR", minor)
        target:set("configvar", "TSET_VERSION_PATCH", patch)
    end)
