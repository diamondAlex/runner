function file_exists(file)
    local f = io.open(file)
    if f then f:close() end
    return f ~= nil
end

function readScripts(file)
    local found = false
    local scripts = {}
    for line in io.lines(file) do
        local name = ""
        local script = ""
        for i=1, #line do
            local c = string.sub(line,i,i)
            if c == ':' then
                found = true
                goto continue
            end
            if found ~= true then
                name = name .. c
            end
            if found then
                script = script .. c
            end
            ::continue::
        end
        scripts[name] = script
        found = false
    end
    return scripts
end

function runScript(scriptName)
    scriptFile = "./runner"
    if file_exists(scriptFile) then
        scripts = readScripts(scriptFile)
        if scripts[scriptName] then 
            os.execute(scripts[scriptName]) 
        end
    else
        print("runner config not found")
        return
    end
end

