Rollout exporter "Burning Rubber Exporter"
(
    button exportall "Export Scene Objects"

	--Export All Necessary Object From Scene
    on exportall pressed do
    (
		--XFile Count
		xfilecount = 0
		
		--Open Export File
		filename = getsavefilename caption:"Save as" type:"gpd file|*.gpd" filename:"*.gpd"
        outfile = createfile filename
		
		--Loop Through Selected Items and export StaticProps
		format "STATIC" to:outfile
		for g in geometry do
		(
			if(findString g.name "staticprop") != undefined then
			(
					--Write Out Matrix Transform
					format "\n%\n%.X\npos %" \
					g.name \
					xfilecount \
					g.transform.row4 to:outfile
				
					--Backup Position & Offset to 0
					position = g.pos
					g.pos = [0,0,0]
								
					--Export X File
					select g
					exportFile(getFilenamePath filename + (xfilecount as string) + ".X") #noPrompt selectedOnly:true using:PandaDirectXMaxExporter
					max select none
				
					--Set position back to original
					g.pos = position
								
					--Increment X File Name
					xfilecount = xfilecount + 1
			)
		)
		format "\nEND\n\n" to:outfile
		
		--Loop Through Selected Items and export Physics Props
		format "PHYSICS" to:outfile
		for g in geometry do
		(
			if(findString g.name "physprop") != undefined then
			(
				--Write Out Matrix Transform
				format "\n%\n%.X\npos %" \
				g.name \
				xfilecount \
				g.transform.row4 to:outfile
				
				--Backup Position & Offset to 0
				position = g.pos
				g.pos = [0,0,0]
				
				--Export X File
				select g
				exportFile(getFilenamePath filename + (xfilecount as string) + ".X") #noPrompt selectedOnly:true using:PandaDirectXMaxExporter
				max select none
				
				--Set position back to original
				g.pos = position
				
				--Increment X File Name
				xfilecount = xfilecount + 1
			)
		)
		format "\nEND\n\n" to:outfile
		
		--Close Export File
		fclose outfile
    )
)

objEd = newRolloutFloater "Burning Rubber Tools" 245 60 50 50
addrollout exporter objEd 




