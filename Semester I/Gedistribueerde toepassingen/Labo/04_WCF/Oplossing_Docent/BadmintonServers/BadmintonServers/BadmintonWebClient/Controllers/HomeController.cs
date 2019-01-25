using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using BadmintonServiceReference;

namespace BadmintonWebClient.Controllers
{
    public class HomeController : Controller
    {
        public IActionResult Index()
        {
            return View();
        }

        public IActionResult About()
        {
            ViewData["Message"] = "Your application description page.";

            return View();
        }

        public IActionResult Contact()
        {
            ViewData["Message"] = "Your contact page.";

            return View();
        }

        public IActionResult Error()
        {
            return View();
        }

        public async Task<IActionResult> Clubs()
        {
            BadmintonServiceClient client = new BadmintonServiceClient();
            SportClub[] sportclubs = await client.GetSportClubsAsync();
            return View(sportclubs);
        }

        public async Task<IActionResult> Leden(int id)
        {
            BadmintonServiceClient client = new BadmintonServiceClient();
            Lid[] leden = await client.GetLedenAsync(id);
            return View(leden);
        }
    }
}
