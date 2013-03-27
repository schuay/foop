note
	description: "Summary description for {PERSON}."
	author: ""
	date: "$Date$"
	revision: "$Revision$"

class
	PERSON

create
	make

feature {NONE} -- Initialization

	make (the_name: STRING)
			-- Initialization for `Current'.
		require
			the_name /= Void
		do
			name := the_name
		end

feature -- Access

	name: STRING

feature -- Status report

	to_string: STRING

		do
			Result := name
		end

invariant
	account_number_not_void: name /= Void

end
