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

	make (account_nr: STRING)
			-- Initialization for `Current'.
		require
			account_nr /= Void
		do
			account_number := account_nr
		end

feature -- Access

feature -- Measurement

feature -- Status report

	to_string: STRING

		do
			Result := account_number
		end

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

	account_number: STRING

invariant
	account_number_not_void: account_number /= Void

end
