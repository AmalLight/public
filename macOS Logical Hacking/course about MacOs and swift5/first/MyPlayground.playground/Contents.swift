//: Playground - noun: a place where people can play

import UIKit // default import

struct Language: Codable {
    
    var name: String
    var versions: Int
    
} // structer like c++

let swift = Language(name: "Swift", versions: 4) // declaration
let php   = Language(name: "PHP",   versions: 7) // declaration
let perl  = Language(name: "Perl",  versions: 6) // declaration

let encoder = JSONEncoder() // building default function

if let encoded = try? encoder.encode(swift) {
    if let json = String(data: encoded, encoding: .utf8) {
        
        print(json)
    }
    
    let decoder = JSONDecoder() // building default function
    
    if let decoded = try? decoder.decode(Language.self, from: encoded) {
        print(decoded.name)

    } // try catch without catch
}


/* three quotes for multiples line */

let longString = """
When you write a string that spans multiple lines make sure you start its content on a line all of its own, and end it with three quotes also on a line of their own. Multi-line strings also let you write "quote marks" freely inside your strings, which is great!
"""


//an example struct
struct Crew {
    var name: String
    var rank: String
}

//another example struct, this time with a method struct Starship
struct Starship {
    var name: String
    var maxWarp: Double
    var captain: Crew
    
    func gotToMaximumWarp () {
        print("\(name) is now travelling at warp \(maxWarp)")
        
        // \(variable_name) like ${variable_name} in JavaScript
    }
}
 
//create instances of those two structs
let janeway = Crew(name: "Kathryn Janeway", rank: "Captain")
let voyager = Starship(name: "Voyager", maxWarp: 9.975, captain: janeway)

//grab a reference to the goToMaximumWarp() method
let enterWarp = voyager.gotToMaximumWarp // invoking of particular function = specifed only for voyager : Starship ( if Typescript )

//call that reference
enterWarp()

/*
  KeyPath: Provides read-only access to a property.
  WritableKeyPath: Provides read|write access to a mutable property.
  ReferenceWritableKeyPath: Provides read|write access to any mutable property.
                            only be used with reference types.
 
  took from : https://www.swiftbysundell.com/articles/the-power-of-key-paths-in-swift/
*/

let nameKeyPath    = \Starship.name
let maxWarpKeyPath = \Starship.maxWarp
let captainName    = \Starship.name

let starshipName    = voyager[keyPath: nameKeyPath    ]
let starshipMaxWarp = voyager[keyPath: maxWarpKeyPath ]
let starshipCaptain = voyager[keyPath: captainName    ]

let cities =
[
    "Shanghai" : 24_256_800,
    "Karachi"  : 23_500_000,
    "Beijing"  : 21_516_000,
    "Seoul"    : 9_995_000
]

// Dictionary in Swift is made from [] not from {} like python .

let massiveCities = cities.filter { $0.value > 10_000_000 }

// filter is like filter for map in R .

let populations = cities.map { $0.value * 2 }

// map return a copy and modified dictionary , useful for piping process .
// $0 for take parent ( this ) value . where this ( c++ ) = self ( python ) = & ( sass ) .

let roundedCities = cities.mapValues { "\($0 / 1_000_000) million people" }

let groupedCities = Dictionary(grouping: cities.keys) { $0.first } // fixed bug !!
print(groupedCities)

let person = ["name": "Taylor", "city": "Nashville"]

let name = person["name", default: "Anonymous"]
// == ( they are equal )
let name2 = person["name"] ?? "Anonymous"

var favoriteTVShows = ["Red Dwarf", "Blackadder", "Fawlty Towers", "Red Dwarf"]

// very faster and strong definition of function , before implement it

var favoriteCounts = [String: Int]()

for show in favoriteTVShows {
    favoriteCounts[show, default: 0] += 1
}

let quote = "It is a truth universally acknowledged that Swift versions bring new features."
let reversed = quote.reversed() // reversed bulding function

for letter in quote {
    
    print(letter)
    
} // tipical foreach

let characters = ["Dr Horrible", "Captain Hammer", "Penny", "Bad Horse", "Moist"]
let bigParts = characters[..<3] // new array from 1 to x , implementing the capture of range of .
let smallerParts = characters[3...] // new array from 3 to y ...

// i think the range start from 0 .

print(bigParts)
print(smallerParts)
