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

	make (the_owner: like owner)
			-- Initialization for `Current'. Note that the expected type of the_owner
			-- depends on owner. For subclasses with covariant types, all we need
			-- to do is redefine owner.
		require
			the_owner /= Void
		do
			owner := the_owner
		end

	double_min_abs: DOUBLE
            -- the minimum deviation of two doubles to be equal
        once
            Result := 0.00000001
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

	set_owner (the_owner: like owner)

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
			str := "ACCOUNT: Owner: " + owner.name + "%N"
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
			(balance - (old balance + delta)).abs <= double_min_abs
		end

	withdraw (delta: DOUBLE)

		require
			min_transaction: delta >= min_transaction
			delta_positive: delta >= 0.0
		do
			balance := balance - delta
		ensure
			(balance - (old balance - delta)).abs <= double_min_abs
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
			--balance = old balance - delta
			(to.balance - (old to.balance + delta)).abs <= double_min_abs
		end

feature -- Public constants

	min_transaction: DOUBLE once Result := 2.0 end

	min_interest: DOUBLE once Result := 0.0 end
	max_interest: DOUBLE once Result := 0.20 end

	min_overdraft_interest: DOUBLE once Result := 0.00 end
	max_overdraft_interest: DOUBLE once Result := 0.80 end

	min_balance: DOUBLE once Result := -2000.00 end

feature {NONE} -- Implementation

invariant
	balance_within_credit_range: balance >= min_balance
	interest_within_range: min_interest <= interest and interest <= max_interest
	overdraft_interest_within_range: min_overdraft_interest <= overdraft_interest and overdraft_interest <= max_overdraft_interest
	owner_not_void: owner /= Void

end
