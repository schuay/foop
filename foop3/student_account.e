note
	description: "Summary description for {STUDENT_ACCOUNT}."
	author: ""
	date: "$Date$"
	revision: "$Revision$"

class
	STUDENT_ACCOUNT

inherit
	ACCOUNT
		redefine
			owner
		end

create
	make

feature {NONE} -- Initialization

feature -- Access

	owner: STUDENT assign set_owner
		-- The owner of this account.

end
