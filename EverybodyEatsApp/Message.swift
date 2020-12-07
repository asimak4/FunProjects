//
//  Message.swift
//  ErryBody Eats
//
//  Created by Ashar Nadeem on 11/24/20.
//

import SwiftUI
import UIKit
import FirebaseAuth

struct Message: Identifiable {
    
    var id : String
    var fromId: String
    var message : String
    var timestamp : Int
    var toId : String
     
 }
