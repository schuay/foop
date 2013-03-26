note
	description: "Summary description for {PENSION_ACCOUNT}."
	author: ""
	date: "$Date$"
	revision: "$Revision$"

class
	SENIOR_ACCOUNT

inherit
	ACCOUNT
		rename
			make as account_make
		end

create
	make

feature {NONE} -- Initialization

	make
			-- Initialization for `Current'.
		do

		end

feature -- Access

feature -- Measurement

feature -- Status report

feature -- Status setting

feature -- Cursor movement

feature -- Element change

feature -- Removal

feature -- Resizing

feature -- Transformation

feature -- Conversion

feature -- Duplication

feature -- Miscellaneous

feature -- Basic operations

feature -- Obsolete

feature -- Inapplicable

feature {NONE} -- Implementation

invariant
	invariant_clause: True -- Your invariant here

end
