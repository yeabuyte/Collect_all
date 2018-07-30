print( "test lua access C++ class" )
 
local function main()
  --local s = Animal:create("xx") 
  local a = TestLua:new(6)
  a:show();
end
 
 local function test(a,b)
	--测试使用
	return a+b;
 end
--main()

for i = 1,10 do
	print(i)
end

if 1 then
	print("test")
end

a = 10
while a < 20 do
print("while")
a = a+1
end

local x=123
local y=456
print("lua:    x(" .. x .. ") + y(" .. y .. ") = " .. lua_add(x, y))

print(test(1,2))
