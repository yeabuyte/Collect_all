print( "test lua access C++ class" )
 
local function main()
  --local s = Animal:create("xx") 
  local a = TestLua:new(6)
  a:show();
end
 
main()
