note
	-- The following comment is a comment describing the description of this class.
	-- just a description of the class
	description: "This class provides the bank account for one person, that is here called owner. It has a balance and some interest rates"
	date: "$Date$"
	revision: "$Revision$"

class
	-- declaration of the class
	ACCOUNT

create
	-- introduces those procedures which can be used to initialize instances
	make

feature {NONE} -- Initialization (like a constructor)

	make (the_owner: like owner)
			-- Initialization for `Current'. Note that the expected type of the_owner
			-- depends on owner. For subclasses with covariant types, all we need
			-- to do is redefine owner.
			-- with like you can use here also subclasses of owner
		require
			-- require defines some preconditions, here the_owner is checked for != NULL
			the_owner /= Void
		do
			-- if precondition is okay, do "do"
			owner := the_owner
		end

feature -- Access, feature defines other methods and attributes of this class

	-- attributes of this class ( attributes_name: type)
	balance: DOUBLE
		-- The current account balance

	owner: PERSON assign set_owner
		-- The owner of this account.

	interest: DOUBLE assign set_interest
		-- Interest paid on positive balances.

	overdraft_interest: DOUBLE
		-- Interest charge on negative balances.

	-- setter-methods of this class ( method_name ( parameter_name: type) )
	set_owner (the_owner: like owner)

		require
			the_owner /= Void
		do
			owner := the_owner
		ensure
			-- ensure defines some postcondition after the "do", that are checked
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

feature -- Status report, just a string output for this class

	to_string: STRING

		local
			-- here you can define local variables for this function
			str: STRING
		do
			str := "ACCOUNT: Owner: " + owner.name + "%N"
			str := str + "Balance: "
			str.append_double (balance)
			str := str + "%N"

			Result := str
			-- Result stands for the return value
		end

feature -- Basic operations

	-- put money on this account
	deposit (delta: DOUBLE)

		require
			min_transaction: delta >= min_transaction
			delta_positive: delta >= 0.0
		do
			balance := balance + delta
		ensure
			double_equals(balance, old balance + delta)
		end

	-- take money from this account
	withdraw (delta: DOUBLE)

		require
			min_transaction: delta >= min_transaction
			delta_positive: delta >= 0.0
		do
			balance := balance - delta
		ensure
			double_equals(balance, old balance - delta)
		end

	-- Transfer money from this account to another account
	transfer (delta: DOUBLE to: ACCOUNT)

		require
			min_transaction: delta >= min_transaction
			delta_positive: delta >= 0.0
			to_not_void: to /= Void
			funds_available: balance - delta >= min_balance
		do
			withdraw (delta)
			to.deposit (delta)
		ensure
			double_equals(balance, old balance - delta)
			double_equals(to.balance, old to.balance + delta)
		end

feature -- Public constants

	min_transaction: DOUBLE once Result := 2.0 end

	min_interest: DOUBLE once Result := 0.0 end
	max_interest: DOUBLE once Result := 0.20 end

	min_overdraft_interest: DOUBLE once Result := 0.00 end
	max_overdraft_interest: DOUBLE once Result := 0.80 end

	min_balance: DOUBLE once Result := -2000.00 end

feature {NONE} -- Implementation

	double_equals (lhs: DOUBLE rhs: DOUBLE): BOOLEAN
		-- Returns true if both lhs and rhs are "almost equal". Handles floating point rounding errors in postconditions.
		do
			Result := (lhs - rhs).abs <= 0.00000001
		end

invariant
	-- this conditions applies to all features that are defined above, its added to every post/precondition of the defined features here
	balance_within_credit_range: balance >= min_balance
	interest_within_range: min_interest <= interest and interest <= max_interest
	overdraft_interest_within_range: min_overdraft_interest <= overdraft_interest and overdraft_interest <= max_overdraft_interest
	owner_not_void: owner /= Void

end
