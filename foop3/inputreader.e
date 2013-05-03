note
	description: "Summary description for {INPUTREADER}."
	author: ""
	date: "$Date$"
	revision: "$Revision$"

class
	INPUTREADER
	create
		make
	feature
		commands : LINKED_LIST [COMMAND]
		newcustomer : NEW_PERSON
		notfound : NOTFOUND
		exit : EXIT
	feature make
	do
		create newcustomer
		create notfound
		create exit
		create commands.make
		commands.extend (newcustomer)
		commands.extend (exit)

	end

	feature
		get_next_command : COMMAND
		do
			io.read_line
			Result := notfound

	        from
	        	commands.start
	        until
	            commands.off

	        loop
	        	if commands.item.get_command.is_equal(io.last_string)
	        	then
	        		Result := commands.item
	        	end
	            commands.forth
	        end
	    ensure
	    	result_not_void: Result /= Void
		end

feature
	list_commands
	do
        print ("AVAILABLE COMMANDS%N")
      	print ("------------------%N")
        from
        	commands.start
        until
            commands.off

        loop
        	print (commands.item.get_command + "%N")
            commands.forth
        end
        print ("------------------%N")
	end

end
