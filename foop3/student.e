note
	description: "this class is a specific person, redefining the printout method"
	date: "$Date$"
	revision: "$Revision$"

class
	STUDENT

inherit
	--this class inherits from person all methods and redefines the method to_string
	PERSON
		redefine
			-- this feature from the upper class will be redefined
			to_string
		end

create
	-- make is already defined in the upper class
	make

feature -- Status report
	-- implemenation of the redefined feature(method)
	to_string: STRING

		do
			Result := "STUDENT: " + Precursor
		end

end
