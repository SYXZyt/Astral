## astral

### Functions
| Name      | Params                 | Returns  | Description																											   |
| --------- | ---------------------- | -------- | ------------------------------------------------------------------------------------------------------------------------ |
| void      | None					 | `void`   | Returns a void type																									   |
| new       | `string` (Struct name) | `struct` | Creates a new struct of the provided type. This function will later be moved to be top-level and not inside of a library |
| get_type  | Value                  | `string` | Returns the type name of a value																						   |
| to_number | `string`               | `number` | Converts a string to a number																							   |
| to_string | Value					 | `string` | Returns the string representation of a value																			   |

## astral.io

### Functions
| Name    | Params   | Returns  | Description                                            |
| ------- | -------- | -------- | ------------------------------------------------------ |
| print   | Value    | `void`   | Will print a value to the screen                       |
| println | Value    | `void`   | Will print a value to the screen followed by a newline |
| input   | None     | `string` | Will read a string from the console and return it      |
| exit    | `number` | `void`   | Stops program execution with a specified exit code     |
| title   | `string` | `void`   | Sets the console window title                          |
| clear   | None     | `void`   | Clear the console window                               |

## astral.string

### Functions
| Name              |  Params                                                    | Returns  | Description                                                |
| -----------------	| ---------------------------------------------------------- | -------- | ---------------------------------------------------------- |
| string_length		|  `string`                                                  | `number` | Counts how many letters are inside a string                |
| string_read		| `string`, `number` (index)                                 | `string` | Reads a character from a string at a given index           |
| string_write		| `string`, `number` (index), `string` (char_to_write)       | `void`   | Writes a character to a string at a given index            |
| binary_from_num	| `number`                                                   | `string` | Returns the binary of a given number. Uses bit count 32    |
| binary_from_num_w | `number`, `number` (bit count)                             | `string` | Returns the binary of a given number and a given bit count |

## astral.maths

### Functions
| Name    | Params                                           | Returns  | Description                                        |
| ------- | ------------------------------------------------ | -------- | -------------------------------------------------- |
| sin     | `number` (angle)                                 | `number` | Calculates sine of an angle                        |
| cos     | `number` (angle)                                 | `number` | Calculates cosine of an angle                      |
| tan     | `number` (angle)                                 | `number` | Calculates tangent of an angle                     |
| asin    | `number`                                         | `number` | Calculates arc sine of a number                    |
| acos    | `number`                                         | `number` | Calculates arc cosine of a number                  |
| atan    | `number`                                         | `number` | Calculates arc tangent of a number                 |
| atan2   | `number` (x) (y)                                 | `number` | Calculates arc tangent of a given coordinate       |
| sqrt    | `number`                                         | `number` | Calculates the square root of a number             |
| log     | `number`                                         | `number` | Calculate natural logarithm of a number            |
| abs     | `number`                                         | `number` | Get the absolute value of a number                 |
| floor   | `number`                                         | `number` | Round a number to the nearest whole towards zero   |
| ceil    | `number`                                         | `number` | Round a number to the nearest whole away from zero |
| round   | `number`                                         | `number` | Round a number to the nearest whole number         |
| clamp   | `number` (min), `number` (max), `number` (value) | `number` | Clamp a value within a range                       |
| min     | `number`, `number`                               | `number` | Returns the lower value of the provided numbers    |
| max     | `number`, `number`                               | `number` | Returns the larger value of the provided numbers   |
| lerp    | `number` (a), `number` (b), `number` (t)         | `number` | Linearly interpolate between two values            |
| sign    | `number`                                         | `number` | Returns the sign of a number                       |
| rad     | `number` (angle in deg)                          | `number` | Converts degrees to radians                        |
| deg     | `number` (angle in rad)                          | `number` | Converts radians to degrees                        |
| and     | `number`, `number`                               | `number` | Calculates a logic and of two binary numbers       |
| not     | `number`                                         | `number` | Calculates a logic not of a binary number          |
| or      | `number`, `number`                               | `number` | Calculates a logic or of two binary numbers        |
| xor     | `number`, `number`                               | `number` | Calculates a logic xor of two binary numbers       |
| shift_l | `number`, `number` (amount)                      | `number` | Shift the bits left of a number by a given amount  |
| shift_r | `number`, `number` (amount)                      | `number` | Shift the bits right of a number by a given amount |

### Variables

PI, TAU, FLT_EPSILON, FLT_MAX, FLT_MIN, INFINITY, NAN