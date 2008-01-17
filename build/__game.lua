function draw()
	if GetKeystate(VK_F1) == 1 then
		PrintText(32,120,"F1 Pressed!")
	end
	if GetKeystate(VK_F2) == 1 then
		PrintText(32,130,"F2 Pressed!")
	end
	PrintText(32,90,"Hello Lua World!")
	PrintText(32,100,"01011001 = Y")
	PrintText(32,110,"RESET!")
	DrawLine(32,32,64,128)
end
