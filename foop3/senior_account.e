note
	description: "Summary description for {PENSION_ACCOUNT}."
	author: ""
	date: "$Date$"
	revision: "$Revision$"

class
	SENIOR_ACCOUNT

inherit
	ACCOUNT
		redefine
			owner
		end

create
	make

feature {NONE} -- Initialization

feature -- Access

	owner: SENIOR assign set_owner
		-- The owner of this account.

end
