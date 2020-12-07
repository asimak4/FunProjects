//
//  User.swift
//  ErryBody Eats
//
//  Created by Ashar Nadeem on 11/24/20.
//
import SwiftUI
import UIKit
import FirebaseAuth

struct User: Identifiable {
    var docid : String = ""
    var id : String = ""
    var email : String = ""
    var first_name : String = ""
    var last_name : String = ""
    var venmoID : String = ""
    var ratingAvg : Float
    var ratingsTotal : Int
}
