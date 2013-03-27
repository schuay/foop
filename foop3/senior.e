note
	description: "Summary description for {SENIOR}."
	author: ""
	date: "$Date$"
	revision: "$Revision$"

class
	SENIOR

inherit
	PERSON
		redefine
			to_string
		end

create
	make

feature -- Status report

	to_string: STRING
		do
			Result := "SENIOR: " + Precursor
		end

end
