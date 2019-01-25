using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;

namespace BadmintonServiceLibrary
{
    [ServiceContract]
    public interface IBadmintonService
    {
        [OperationContract]
        SportClub[] GetSportClubs();

        [OperationContract]
        Lid[] GetLeden(int sportclubID);
    }

    [DataContract]
    public class SportClub
    {
        [DataMember]
        public int ID { get; set; }

        [DataMember]
        public String Naam { get; set; }

        [DataMember]
        public Tornooi[] Tornooien { get; set; }
    }

    [DataContract]
    public class Lid
    {
        [DataMember]
        public int ID { get; set; }

        [DataMember]
        public String Naam { get; set; }
    }

    [DataContract]
    public class Tornooi
    {
        [DataMember]
        public int ID { get; set; }

        [DataMember]
        public String Naam { get; set; }
    }
}
