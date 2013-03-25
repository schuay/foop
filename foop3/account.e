note
	description: "Summary description for {ACCOUNT}."
	author: ""
	date: "$Date$"
	revision: "$Revision$"

class
	ACCOUNT

create
	make

feature {NONE} -- Initialization

	make (the_owner: PERSON)
			-- Initialization for `Current'.
		require
			the_owner /= Void
		do
			owner := the_owner
		end

feature -- Access

	get_balance: DOUBLE
		do
			Result := balance
		end

feature -- Measurement

feature -- Status report

	to_string: STRING

		local
			str: STRING
		do
			str := "Owner: " + owner.to_string + "%N"

			str := str + "Balance: "
			str.append_double (balance)
			str := str + "%N"

			Result := str
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

	deposit (delta: DOUBLE)

		require
			min_transaction: delta >= min_transaction
			delta_positive: delta >= 0.0
		do
			balance := balance + delta
		ensure
			balance = old balance + delta
		end

	withdraw (delta: DOUBLE)

		require
			min_transaction: delta >= min_transaction
			delta_positive: delta >= 0.0
		do
			balance := balance - delta
		ensure
			balance = old balance - delta
		end

	transfer (delta: DOUBLE, to: ACCOUNT)

		require
			min_transaction: delta >= min_transaction
			delta_positive: delta >= 0.0
		do
			-- TODO
		ensure
			balance = old balance - delta
		end

feature -- Public constants

	min_transaction: DOUBLE is 2.00

	min_interest: DOUBLE is 0.00
	max_interest: DOUBLE is 0.20

	min_balance: DOUBLE is -2000.00

feature {NONE} -- Implementation

	owner: PERSON

	balance: DOUBLE
	interest: DOUBLE

invariant
	balance_within_credit_range: balance >= min_balance
	interest_within_range: min_interest <= interest and interest <= max_interest
	owner_not_void: owner /= Void

end
