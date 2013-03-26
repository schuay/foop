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

	balance: DOUBLE
		-- The current account balance

	owner: PERSON assign set_owner
		-- The owner of this account.

	interest: DOUBLE assign set_interest
		-- Interest paid on positive balances.

	overdraft_interest: DOUBLE
		-- Interest charge on negative balances.

	set_owner (the_owner: PERSON)

		require
			the_owner /= Void
		do
			owner := the_owner
		ensure
			owner = the_owner
		end

	set_interest (the_interest: DOUBLE)

		do
			interest := the_interest
		ensure
			interest = the_interest
		end

	set_overdraft_interest (the_overdraft_interest: DOUBLE)

		do
			overdraft_interest := the_overdraft_interest
		ensure
			overdraft_interest = the_overdraft_interest
		end

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

	transfer (delta: DOUBLE to: ACCOUNT)
		-- Transfer money from this account to another account
		require
			min_transaction: delta >= min_transaction
			delta_positive: delta >= 0.0
			to_not_void: to /= Void
			funds_available: balance - delta >= min_balance
		do
			withdraw (delta)
			to.deposit (delta)
		ensure
			balance = old balance - delta
			to.balance = old to.balance + delta
		end

feature -- Public constants

	min_transaction: DOUBLE is 2.00

	min_interest: DOUBLE is 0.00
	max_interest: DOUBLE is 0.20

	min_overdraft_interest: DOUBLE is 0.00
	max_overdraft_interest: DOUBLE is 0.80

	min_balance: DOUBLE is -2000.00

feature {NONE} -- Implementation

invariant
	balance_within_credit_range: balance >= min_balance
	interest_within_range: min_interest <= interest and interest <= max_interest
	overdraft_interest_within_range: min_overdraft_interest <= overdraft_interest and overdraft_interest <= max_overdraft_interest
	owner_not_void: owner /= Void

end
