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
		commands : attached LINKED_LIST [NEWCUSTOMER]
		newcustomer : attached NEWCUSTOMER
		notfound : NOTFOUND
	feature make
	do
		create newcustomer
		create notfound
		create commands.make
		commands.extend (newcustomer)

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
        	if commands.item.get_command = io.last_string
        	then
        		Result := commands.item
        	end
            commands.forth
        end
	end

feature
	list_commands
	do
        from
        	commands.start
        until
            commands.off

        loop
        	print ("AVAILABLE COMMANDS%N")
        	print ("------------------%N")
        	print (commands.item.get_command + "%N")
        	print ("------------------%N")

            commands.forth
        end
	end

end
