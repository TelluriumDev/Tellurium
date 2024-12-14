add_rules("mode.debug", "mode.release")

add_repositories("liteldev-repo https://github.com/LiteLDev/xmake-repo.git")
add_repositories("groupmountain-repo https://github.com/GroupMountain/xmake-repo.git")

add_requires(
    "levilamina 0.13.5",
    "preloader v1.12.0",
    "gmlib 0.13.7"
)

if not has_config("vs_runtime") then
    set_runtimes("MD")
end

option("tests")
    set_default(false)
    set_showmenu(true)
    set_description("Enable tests")

target("Tellurium")
    add_cxflags(
        "/EHa",
        "/utf-8",
        -- "/W4",
        "/WX",
        "/w44265",
        "/w44289",
        "/w44296",
        "/w45263",
        "/w44738",
        "/w45204"
    )
    add_defines(
        "NOMINMAX", 
        "UNICODE", 
        "_HAS_CXX17",
        "_HAS_CXX20",
        "_HAS_CXX23",
        "TU_EXPORT"
    )
    add_files("src/**.cpp")
    add_headerfiles("src/(Tellurium/**.h)")
    add_includedirs("src")
    add_packages(
        "levilamina",
        "preloader",
        "gmlib"
    )
    add_shflags("/DELAYLOAD:bedrock_server.dll")
    set_exceptions("none")
    set_kind("shared")
    set_languages("c++20")
    set_symbols("debug")

    if is_mode("debug") then
        add_defines("TU_DEBUG")
    end

    if has_config("tests") then
        add_defines("TU_TESTS")
        add_includedirs("src-test/")
        add_headerfiles("src-test/**.h")
        add_files("src-test/**.cpp")
    end

    after_build(function (target)
        local version, suffix = os.iorun("git describe --tags --abbrev=0 --always"):match("^v([0-9+].[0-9+].[0-9+])(.*)")
        if not version then
            version = "0.0.0"
        end

        local output_directory = path.join(os.projectdir(), "bin", target:name())
        if os.exists(output_directory) then -- remove old build
            os.rm(output_directory)
        end

        if not os.isfile(path.join(os.projectdir(), "manifest.json")) then
            return cprint("${bright red}error: ${reset}not found manifest.json in root dir!")
        end

        local manifest_path = path.join(output_directory, "manifest.json")
        os.cp(path.join(os.projectdir(), "manifest.json"), manifest_path)

        local mod_define = {
            modName = target:name(),
            modFile = path.filename(target:targetfile()),
            modVersion = version,
        }

        io.gsub(manifest_path, "%${(.-)}", function(var)
            return tostring(mod_define[var]) or "${" .. var .. "}"
        end)

        os.cp(target:targetfile(), path.join(output_directory, target:name() .. ".dll"))

        os.cp(path.join(os.projectdir(), "lang"), path.join(output_directory, "lang"))

        local pdb_path = path.join(output_directory, target:name() .. ".pdb")
        if os.isfile(target:symbolfile()) then
            os.cp(target:symbolfile(), pdb_path)
        end

        cprint("${bright green}[mod Packer]: ${reset}mod already generated to " .. output_directory)
    end)
